#include "wxml.h"

#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char* strcatalloc(char* dst, const char* src) {
	int l = dst ? strlen(dst) : 0;
	int s = strlen(src);

	dst = realloc(dst, l + s + 1);
	memcpy(dst + l, src, s);

	dst[l + s] = 0;

	return dst;
}

void child_str(char** data, wxml_node_t* n) {
	if(n->name) {
		*data = strcatalloc(*data, "<");
		*data = strcatalloc(*data, n->name);

		if(n->attrs.count > 0) {
			for(int i = 0; i < n->attrs.count; ++i) {
				char* s = malloc(strlen(n->attrs.names[i]) + strlen(n->attrs.values[i]) + 5);
				sprintf(s, " %s=\"%s\"", n->attrs.names[i], n->attrs.values[i]);

				*data = strcatalloc(*data, s);
				free(s);
			}
		}
	}

	if(n->child_count == 0) {
		if(n->content) {
			*data = strcatalloc(*data, ">");
			*data = strcatalloc(*data, n->content);
		}
		else {
			*data = strcatalloc(*data, " />");
			return;
		}
	}
	else {
		if(n->name) {
			*data = strcatalloc(*data, ">");
		}

		for(int i = 0; i < n->child_count; ++i) {
			child_str(data, n->childs + i);
		}
	}

	if(n->name) {
		char* s = malloc(strlen(n->name) + 4);
		sprintf(s, "</%s>", n->name);

		*data = strcatalloc(*data, s);
		free(s);
	}
}

wxml_doc_t wxml_doc_create() {
	wxml_doc_t doc;
	doc.root = malloc(sizeof(wxml_node_t));

	doc.root->name = 0;
	doc.root->attrs = (wxml_attrs_t){0};
	doc.root->childs = 0;
	doc.root->child_count = 0;
	doc.root->content = 0;

	return doc;
}

char* wxml_doc_serialize(wxml_doc_t* doc) {
	char* data = 0;
	child_str(&data, doc->root);

	return data;
}

wxml_node_t* wxml_node_add(wxml_node_t* parent, const char* name) {
	if(!parent) {
		return 0;
	}

	parent->childs = realloc(parent->childs, (++parent->child_count) * sizeof(wxml_node_t));

	wxml_node_t* n = &parent->childs[parent->child_count - 1];
	n->name = name;
	n->attrs = (wxml_attrs_t){0};
	n->childs = 0;
	n->child_count = 0;
	n->content = 0;

	return n;
}

void wxml_node_content(wxml_node_t* node, const char* content) {
	node->content = content;
}

void wxml_attr_add(wxml_node_t* node, const char* name, const char* value) {
	node->attrs.count++;
	node->attrs.names = realloc(node->attrs.names, node->attrs.count * sizeof(char**));
	node->attrs.values = realloc(node->attrs.values, node->attrs.count * sizeof(char**));

	node->attrs.names[node->attrs.count - 1] = (char*)name;
	node->attrs.values[node->attrs.count - 1] = (char*)value;
}

void wxml_node_free(wxml_node_t* node) {
	for(int i = 0; i < node->child_count; ++i) {
		wxml_node_free(node->childs + i);
	}

	free(node->childs);

	if(node->attrs.count > 0) {
		free(node->attrs.names);
		free(node->attrs.values);
	}
}

void wxml_doc_free(wxml_doc_t* doc) {
	wxml_node_free(doc->root);
	free(doc->root);
}

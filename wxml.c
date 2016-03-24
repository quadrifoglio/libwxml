#include "wxml.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

wxml_doc_t wxml_doc_create() {
	wxml_doc_t doc;

	doc.root.name = 0;
	doc.root.attrs = (wxml_attrs_t){0};
	doc.root.childs = 0;
	doc.root.child_count = 0;
	doc.root.content = 0;

	return doc;
}

void childs(wxml_node_t* n) {
	if(n->name) {
		printf("<%s", n->name);

		if(n->attrs.count > 0) {
			for(int i = 0; i < n->attrs.count; ++i) {
				printf(" %s=\"%s\"", n->attrs.names[i], n->attrs.values[i]);
			}
		}

		printf(">");
	}

	if(n->content) {
		printf("%s", n->content);
	}
	else {
		for(int i = 0; i < n->child_count; ++i) {
			wxml_node_t child = n->childs[i];
			childs(&child);
		}
	}

	if(n->name) {
		printf("</%s>", n->name);
	}
}

char* wxml_doc_serialize(wxml_doc_t* doc) {
	char* data = calloc(1, 1);

	childs(&doc->root);

	return data;
}

wxml_node_t* wxml_node_add(wxml_node_t* parent, const char* name, const char* content) {
	if(!parent) {
		return 0;
	}

	parent->childs = realloc(parent->childs, (++parent->child_count) * sizeof(wxml_node_t));

	wxml_node_t* n = &parent->childs[parent->child_count - 1];
	n->name = name;
	n->attrs = (wxml_attrs_t){0};
	n->childs = 0;
	n->child_count = 0;
	n->content = content;

	return n;
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
	wxml_node_free(&doc->root);
}

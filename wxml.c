#include "wxml.h"
#include <stdlib.h>

wxml_doc_t wxml_doc_create() {
	wxml_doc_t doc;

	doc.nodes = 0;
	doc.node_index = 0;
	doc.node_count = 0;

	return doc;
}

char* wxml_doc_serialize(wxml_doc_t* doc) {
	char* data = calloc(1, 1);
	return data;
}

wxml_node_t* wxml_node_root(wxml_doc_t* doc) {
	return wxml_node_add(doc, 0, "");
}

wxml_node_t* wxml_node_add(wxml_doc_t* doc, wxml_node_t* parent, const char* name) {
	doc->nodes = realloc(doc->nodes, (++doc->node_count) * sizeof(wxml_node_t));

	wxml_node_t* n = &doc->nodes[doc->node_index++];
	n->parent = parent;
	n->name = name;
	n->attrs = (wxml_attrs_t){0};

	return n;
}

void wxml_attr_add(wxml_node_t* node, const char* name, const char* value) {
	node->attrs.count++;
	node->attrs.names = realloc(node->attrs.names, node->attrs.count * sizeof(char**));
	node->attrs.values = realloc(node->attrs.values, node->attrs.count * sizeof(char**));

	node->attrs.names[node->attrs.count - 1] = (char*)name;
	node->attrs.values[node->attrs.count - 1] = (char*)value;
}

void wxml_doc_free(wxml_doc_t* doc) {
	for(int i = 0; i < doc->node_count; ++i) {
		free(doc->nodes[i].attrs.names);
		free(doc->nodes[i].attrs.values);
	}

	free(doc->nodes);
}

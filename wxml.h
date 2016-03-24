#pragma once

#define false 0
#define true 1

typedef _Bool bool;

typedef struct wxml_attrs wxml_attrs_t;
typedef struct wxml_node wxml_node_t;
typedef struct wxml_doc wxml_doc_t;

struct wxml_attrs {
	char** names;
	char** values;
	int count;
};

struct wxml_node {
	wxml_node_t* parent;

	const char* name;
	wxml_attrs_t attrs;
};

struct wxml_doc {
	wxml_node_t* nodes;

	int node_index;
	int node_count;
};

wxml_doc_t    wxml_doc_create();
char*         wxml_doc_serialize(wxml_doc_t* doc);
wxml_node_t*  wxml_node_root(wxml_doc_t* doc);
wxml_node_t*  wxml_node_add(wxml_doc_t* doc, wxml_node_t* parent, const char* name);
void          wxml_attr_add(wxml_node_t* node, const char* name, const char* value);
void          wxml_doc_free(wxml_doc_t* doc);

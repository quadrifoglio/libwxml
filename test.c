#include <stdio.h>
#include <stdlib.h>

#include "wxml.h"

int main(void) {
	wxml_doc_t docv = wxml_doc_create();
	wxml_doc_t* doc = &docv;

	wxml_node_t* root = wxml_node_root(doc);

	wxml_node_t* html = wxml_node_add(doc, root, "html");
	wxml_attr_add(html, "lang", "fr");

	wxml_node_t* head = wxml_node_add(doc, html, "head");
	wxml_node_t* title = wxml_node_add(doc, head, "title");

	wxml_node_t* body = wxml_node_add(doc, html, "body");
	wxml_node_t* h1 = wxml_node_add(doc, body, "h1");

	char* data = wxml_doc_serialize(doc);
	puts(data);
	free(data);

	wxml_doc_free(doc);
	return 0;
}

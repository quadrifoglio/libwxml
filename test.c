#include <stdio.h>
#include <stdlib.h>

#include "wxml.h"

int main(void) {
	wxml_doc_t doc = wxml_doc_create();
	wxml_node_t* root = doc.root;

	wxml_node_t* html = wxml_node_add(root, "html");
	wxml_attr_add(html, "lang", "fr");

	wxml_node_t* head = wxml_node_add(html, "head");

	wxml_node_t* title = wxml_node_add(head, "title");
	wxml_node_content(title, "Test");

	wxml_node_t* body = wxml_node_add(html, "body");

	wxml_node_t* h1 = wxml_node_add(body, "h1");
	wxml_node_content(h1, "Hello world !");

	char* data = wxml_doc_serialize(&doc);
	puts(data);
	free(data);

	wxml_doc_free(&doc);
	return 0;
}

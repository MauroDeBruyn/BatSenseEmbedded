#ifndef WEBDATA_H
#define WEBDATA_H

static const char PAGE_ERR_HTML[] =
"<!doctype html>\n"
"<body style=\"margin:0;display:flex;justify-content:flex-end;align-items:flex-start;"
"height:100vh;background:#afb6fa;color:#080a1c;\">\n"
"<pre style=\"margin:0;text-align:right;white-space:pre-wrap;\">%s</pre>\n"
"</body>\n";


static const char PAGE_HTML[] =
"<!doctype html>\n"
"<body style=\"margin:0;display:flex;justify-content:center;align-items:center;height:100vh;background:#afb6fa;color:#080a1c;\">\n"
"This will be the page from which files will be downloaded and %s\n"
"</body>\n";
#endif
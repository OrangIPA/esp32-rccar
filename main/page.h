#pragma once

const char* html_page =
"<!DOCTYPE html>\n"
"<html>\n"
"  <head>\n"
"    <title>Mobil Resing</title>\n"
"  </head>\n"
"  <body>\n"
"    <p><button id=\"maju\" style=\"user-select:none; -webkit-user-select: none; -moz-user-select: none; -webkit-touch-callout: none;\">Maju</a></p>\n"
"    <script>\n"
"      const maju = document.getElementById(\"maju\");\n"
"      maju.addEventListener(\"touchstart\", (e) => {fetch('/maju');e.preventDefault()}, {passive: false})\n"
"      maju.addEventListener(\"touchend\", () => fetch('/stop'))\n"
"    </script>\n"
"  </body>\n"
"</html>\n";

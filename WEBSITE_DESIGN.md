# WEBSITE DESIGN

## Unit Documentation

### https://zetaglest.github.io/

The repo is at https://github.com/ZetaGlest/zetaglest.github.io

#### Files in the root folder

Files are published to the web site automatically when the repo is updated.

The style sheet is in [media](https://github.com/ZetaGlest/zetaglest.github.io/tree/master/convert_faction_xml2html/media)

And it's copied to the root folder of the website when the
[perl script](https://github.com/ZetaGlest/zetaglest.github.io/blob/master/convert_faction_xml2html/convert_faction_xml2html.pl)
is run. The script generates the html (which is how you'd preview your
changes).

Part of the template for the site is in the perl script, and another part is in
[an ini file](https://github.com/ZetaGlest/zetaglest.github.io/blob/master/convert_faction_xml2html/zetapack.ini).

## Primary documentation

### Files in [docs](https://github.com/ZetaGlest/zetaglest.github.io/tree/master/docs)

See the [README in that folder](https://github.com/ZetaGlest/zetaglest.github.io/blob/master/docs/README)
for an explanation of how to edit the html files in zetaglest.github.io/docs.

## Server list and player stats

### https://zetaglest.dreamhosters.com/

The repo is at

https://github.com/ZetaGlest/zetaglest-masterserver

These instructions assume you are familiar with testing php and mysql changes

These 2 files should allow you to set up the database and, using the code
from the master-server repo, view how the web page would look. It should look similar to this:<br />
https://zetaglest.dreamhosters.com/

 * [exported database](https://github.com/ZetaGlest/zetaglest-masterserver/blob/develop/docs/mysql_zetaglest_dreamhosters_com_exported_20180616.sql) in SQL format
 * [database scheme file](https://github.com/ZetaGlest/zetaglest-masterserver/blob/develop/install/scheme_mysql.sql)

Once you've confirmed that a web page will display, you can edit the
PHP, html, and CSS and test your changes locally.


CONTENTS OF THIS FILE
---------------------

 * Introduction
 * Requirements
 * Installation
 * Configuration
 * Usage
 * Known issues
 * Upgrade notes
 * Further reading
 * Developer docs


INTRODUCTION
------------

"I love all my media having thumbnails - PERIOD."

Some time ago i found the PDF project. Awesome attempt
to do kinda what i wanted, but not completely.

Just a couple of days ago i found the PDF Thumb project,
again awesome work, but it required configurations i
didn't needed, nor wanted, i just want PDF's and Thumbnails!

So last sunday i started hacking a bit, the result is PDF NG.

True, some parts could be done better and so, it still needs a
bit of work, in fact, it's more a proof of concept for now, but
it does work great for what i need it for: create thumbnails
for PDF's (only the first page) and display them - everywhere.


REQUIREMENTS
------------

What do you need:
- ImageMagick
- PDF.js

Drupal modules:
- file_entity (requires the 2.x version from a date after march 8th 2013).
- libraries


INSTALLATION
------------

Download PDF.js:

Uncompiled: (requires you to build PDF.js and we also suggest
to minify it, see FURTHER READING below).
https://github.com/mozilla/pdf.js

Compiled:
https://github.com/mozilla/pdf.js/tags

Extract the pdf.js package to the [SITE_ROOT]/sites/all/libraries/ folder.

Install imagemagick:
apt-get install imagemagick

And make sure your site has access to /usr/bin/convert.
TODO: It's hardcoded for now, but we might patch it at some point.


CONFIGURATION
-------------

Configure the file view modes you want PDF's to show up for.

By default only the thumbnail is displayed.

(cause some people have like a gazillion PDF's on their sites,
and if someone messed up the view modes, that might lead to
'undesired behaviour' aka possibly broken sites.)

Do NOT NEVER EVER use or change the 'preview' mode.
This mode is used on the node form, media browser, etc.


USAGE
-----

Crazy time! Finally we can do some insane things like:
- Create a PDF slideshow with the thumbnails from the pdf linked to the node - or - the pdf itself.
- Create a Colorbox popup that uses the thumbnail as a trigger / link.
- Media browser with friggin' PDF thumbnails! YAY!
- Link to a PDF file in a new window.
- Link a pdf thumbnail on the teaser to the node.
- and more.

Just add a new view mode via the 'entity view mode' module and configure view modes according.


Link strategy: The module supports a couple options to link to a pdf file.

Teaser thumbnail: if you install the 'file_entity_link' module, you can
set up a link to the referencing node entity, this is useful to link
thumbnails used in a teaser view to the node.

Link to the pdf in a new window: Manage the file display for the
'Document' file type. Make sure 'PDF thumbnail' is enable.
You will see 3 options below the Image style:
 Show name
  - If checked, the file name will be displayed above the thumbnail.
 Link to
  - If checked, the thumbnail will link to the PDF file.
 New window
  - If checked, the linked thumbnail will open in a new tab/window.

The link to and new window are the most interesting. These options
allow to fine tune the link a bit, open the document in a new window,
or in the same window.

I have also added a 'PDF Link' display mode. This renders a link
to the pdf file loaded in pdf.js, optionally in a new window.


How to configure this all with colorbox?

Install media_colorbox and the entity view mode module.

Create 3 new entity view modes for the 'file' entity, name them something like:
- PDF Colorbox Thumbnail
- PDF Colorbox Document
- PDF Colorbox Trigger

Create a new image style for the thumbnail. Let's make it 90x130 pixels.

Edit the 'Colorbox Thumbnail' document file display
Set the display to 'image' and select the
thumbnail you created in the previous step.

Visit admin/structure/file-types/manage/document/file-display and edit
the new entity view modes:
- Enable 'Media Colorbox' on the PDF trigger.
- Set the 'File view mode' to PDF Colorbox Thumbnail.
- Set the 'Colorbox view mode' to PDF Colorbox Document.



Save everything and enjoy the ride!


KNOWN ISSUES
------------

A boatload for sure, but it's not my focus at the moment to fix any.
(But would be neat to get some funding together to get this started).

I'm willing to apply patches, so if you have a patch, start an issue.


pdf_ng_process_file($file)
Possible TODO: add option to file upload in some crazy way to
set the page we want to 'thumbnail' (or maybe even multiple).
The [0] bit limits to page 1, see pdf_ng_process_file().

Included in this TODO are:
- We have to decide how to save the file. Maybe people want to create multiple thumbnails?
  Crazy, but possible. We could render a list of pages during upload? (maybe)
  So people can just click on the pages they want to have 'thumbnailed'.
  Then they would also have to set one of those images as 'the default', to save with the content.
  And those remaining files still have to be linked to the content / file entity in some way.

- Update theme functions to work with multiple thumbnail files. (maybe create a new display mode for this).

Or just check if the first file exists with -0 and if that exists, use it.
Just copy it to a name without -0) (leading to kinda what we currently have).
http://drupal.stackexchange.com/questions/24228/check-if-unmanaged-file-exists

So for now we just use the first thumb, this works fine in most situations. If people want to
change the thumbnail,they can create a thumb themselves and replace it via the edit file page.


UPGRADE NOTES
-------------

   ___   _   ___ _  ___   _ ___  __   _____  _   _ ___   ___   _ _____ _   
  | _ ) /_\ / __| |/ / | | | _ \ \ \ / / _ \| | | | _ \ |   \ /_\_   _/_\  
  | _ \/ _ \ (__| ' <| |_| |  _/  \ V / (_) | |_| |   / | |) / _ \| |/ _ \ 
  |___/_/ \_\___|_|\_\\___/|_|     |_| \___/ \___/|_|_\ |___/_/ \_\_/_/ \_\

Don't say we didn't warn you, always create backups before attempting an
upgrade and test a (partial) upgrade on a test server or your local machine.

But we got nothing to upgrade! So no worries. Actually, i do not expect huge things we can do
here, we only display files that already exist on the system, so it should just work.

For existing files we do need to do some work. While the render-bit could simply create
thumbnails that do not exist, i believe it would be a better idea to add some other
way to accomplish this, like some cron function, or special page you can visit.


FURTHER READING
---------------

Howto minify PDF.js:
https://github.com/mozilla/pdf.js/issues/710#issuecomment-4080540)


Quick explanation of the workings:

We use the same style most media_xyz modules use to render a thumbnail
or a file (pdf) for the application/pdf mimetype.

The module uses the PDF.js and ImageMagick applications to accomplish
this without to much code to maintain on the Drupal side of things.

While it's true the PDF module facilicates the use of the pdf.js
worker_loader.js script and pdf.js to create a thumbnail on the fly,
i required the actual thumbnails, for display on product nodes, saved
on the file system. (And i've found this part is kinda buggy in some
browsers, so it was a no-go for me, and thus, i started coding).

We have template files for the pdf and the thumbnail! YAY! Let the modding commence!

And i wanted an option to AND render a PDF in a colorbox popup AND render a thumbnail
with a simple link to the actual PDF, opening in the same or _blank window.


More techical differences between PDF / PDFThumb and this module?

PDF uses hook_field_formatter_info(), we use hook_file_formatter_info().
In other words, we depend on file_entity, making more crazy stuff
possible and not limiting this in any way to a field.

PDFThumb uses hook_entity_presave(), we use hook_file_insert() and check
the mimetype, we want this to run for all PDF's EVERYWHERE they are saved
/ used, not limited to a field we need to configure.

PDFThumb also creates a list of options, we do not have any options for
fields to create thumbnails, we do not use the field, we use the file.
This enables us to generate a thumbnail everywhere, even on node view and
use it directly in all view modes we want, including the node edit form.

PDFThumb is limited to the first PDF in the file collection, we do not use
this, so we are not limited in any way.

PDFThumb also creates a new database table to link the thumbnail to the pdf,
PDF NG uses the file name as a reference, just like most media_xyz modules do
to get to the correct thumbnail. We render the pdf document 'image' inside
a separate theme function and we have 2 templates, for images and pdf files.

We use the filemime to act on file actions, not the type.


/ PDF NG 7.x-1.x-dev README.

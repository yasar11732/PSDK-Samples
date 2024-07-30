=============================================
XML -- XML RDF Viewer
=============================================
Last Updated: October 28, 1999.


SUMMARY
========
This sample demonstrates how to retrieve and view the contents of RDF files. 
The Resource Description Framework (RDF) is a framework for describing metadata. 
RDF uses XML. It is designed so that Web sites can supply metadata in an easy to 
use fashion. Using RDF a Web site can create a metadata file that describes the 
site’s content. The file can then be parsed for an understanding of what is on 
the site. 

The sample is written in Visual Basic 6.0 and consists of a single form. Users 
can enter the URL of a known RDF file or they can choose buttons that represent 
RDF files from three different sources. The form then retrieves the RDF file, 
which is then parsed using the MSXML parser. The contents of the RDF file are 
presented in a list box and any URL links attached to each item are stored in 
an array. When an item in the list box is selected, the page represented by the 
associated URL is displayed in the Browser control.


USAGE
======
The form has buttons for MacWeek and ExoScience. Choosing MacWeek retrieves news 
headlines from the URL http://macweek.zdnet.com/macweek.xml. Choosing ExoScience 
retrieves news headlines from the URL http://exosci.com/exosci.rdf. During testing 
of the sample application these links worked most of the time. However, you may 
find on any given day that choosing either of these buttons does not return any 
XML data.

An excellent source for finding sites that provide data in XML is 
http://www.xmltree.com. This site provides searching capabilities and also 
groups sites by category. Use XMLTree to find a site that provides data in XML 
and then enter the URL of that site in the form. Note that the extension used 
on the RDF file may vary. For instance, the URL for Beta News headlines is 
http://betanews.com/mnn.php3, while the URL for the Motley Fool headlines is 
http://www.fool.com/about/headlines/rss_headlines.asp.

To run the XML RDF Viewer application, open the Visual Basic Project file 
(XMLRDFViewer.vpb) with Visual Basic 6.0 and click on 'Start'. Click on either 
the MacWeek or ExoScience button to display the XML content. Click on any one 
of the headings to display the web content inside the browser window.


REQUIREMENTS
=============
This sample requires Visual Basic 6.0 and Windows 98, Windows NT 4.0, or 
Windows 2000.


SOURCE FILES
==============
XMLRDKViewer.frm
XMLRDKViewer.frx
XMLRDKViewer.vbp
XMLRDKViewer.vbw

OTHER FILES
============
Readme.txt
XMLRDFViewer.doc
exoscience.gif
macweekcom.gif


==============================
© Microsoft Corporation 1999

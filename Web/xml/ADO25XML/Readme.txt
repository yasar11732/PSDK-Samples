=============================================
XML -- Streams and XML in ADO 2.5
=============================================
Last Updated: October 25, 1999.


SUMMARY
========
This sample demonstrates how to use the new Stream object in ADO 2.5 
to read a recordset into XML and vice versa. A Stream object provides 
the means to read, write, and manage the binary stream of bytes or text 
that comprise a file or message stream. In ADO 2.1 you can save a recordset 
to XML that is persisted to disk using the Save method and the adPersistXML 
option.

	rst.Save "pubs.xml", adPersistXML

You can open a recordset based on the XML file with the Open method.

	rst.Open "pubs.xml"

In ADO 2.5 you can use the Stream object to work with XML without having 
to write it to disk first. The Stream object exists in memory. In this 
sample the contents of a recordset are converted to XML and then written 
to the Stream object, which is named st here.

	rs.Save st, adPersistXML

Just as a recordset can be opened from an XML file, it can also be opened 
based on the XML in a Stream.

	rs.Open st


SETUP
======
The sample retrieves data from the SQL Server 7.0 Northwind sample database. 
The connection string in the procedure btnRetrieve_Click has the following:

	DataSource=(local);

If the SQL Server you are using is on a different machine you must use the name 
of that machine instead, for example if SQL Server is on a machine named Cocoa, 
you would use the following:

	DataSource=Cocoa;


USAGE
======
The sample consists of a single form. Choose Retrieve to run a query and 
populate a grid with a list of products. The data resides in an ADO recordset. 
To apply a filter to the product list enter the filter expression and choose 
Apply. For example you might enter the following as a filter expression:

	unitprice > 10

Only the records that meet the filter criteria appear in the grid. To remove 
the filter choose Clear. 

To convert the contents of the ADO recordset to XML, choose ADO -> XML. The 
contents of the XML appear in the bottom half of the form. 

To create an ADO recordset from the XML choose XML -> ADO. The contents of 
the recordset are displayed in the grid. 


REQUIREMENTS
=============
This sample requires Visual Basic 6.0 and Active Data Objects (ADO) 2.5. 
It can be run under Windows 98, Windows NT 4.0, or Windows 2000. ADO 2.5 
ships with Windows 2000 and will also be downloadable from Universal Data Access 
Online.

Note: This content uses a beta of ADO 2.5 and is therefore for preview only 
and subject to change.


SOURCE FILES
==============
ADOXML.vbp
ADOXML.vbw
frmADOXML.frm
frmADOXML.frx


OTHER FILES
============
Readme.txt
Readme.doc
 

SEE ALSO
=========
Microsoft Universal Data Access at http://www.microsoft.com/data.



==============================
© Microsoft Corporation 1999

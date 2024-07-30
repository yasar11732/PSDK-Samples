<%@ Language=JavaScript %>
<%

// Generate the correct HTTP headers to signify that this is an XML stream 
Response.ContentType = "text/xml";
Response.Expires = 0;
%>
<?xml version="1.0"?>
<%
// Create an instance of the XML Parser object
var objXMLParser = new ActiveXObject( "Microsoft.XMLDOM" );

// Create an instance of our Adapter object
var objAdapter = new ActiveXObject( "RequestExLib.RequestEx" );

// Retrieve the body of the HTTP Post request. The Adapter object does
// the right thing based on whether we're running IIS 4.0 or IIS 5.0
objAdapter.Adapt( objXMLParser );

// Retrieve the parameters passed from the client
var strComputer = objXMLParser.selectSingleNode( "//computer" ).text;
var strDatabase = objXMLParser.selectSingleNode( "//database" ).text;
var strSQL = objXMLParser.selectSingleNode( "//sql" ).text;

// Generate the OLE DB connection string
var strConn = "Provider=SQLOLEDB.1;Persist Security Info=False;User ID=sa;Initial Catalog=";
strConn += strDatabase + ";Data Source=" + strComputer;

// Create an ADO recordset object
var objRS = new ActiveXObject( "ADODB.Recordset" );

// NOTE: usage of .valueOf() is essential to ensure that value is converted to 
// the appropriate type (string) that ADO is expecting. The type that it was 
// going in was an IDispatch objref.
objRS.Open( strSQL.valueOf(), strConn );

// Note that we have a conditional here to allow this sample to run using both
// IIS 4.0 and IIS 5.0
if( Request.ServerVariables( "SERVER_SOFTWARE" ) == "Microsoft-IIS/5.0" ) {
	objRS.Save( Response, adPersistXML );
} else {
	var objFS, strFilename, strTempFolder, objTextStream;
	objFS = Server.CreateObject( "Scripting.FileSystemObject" );
	strTempFolder = objFS.GetSpecialFolder( TemporaryFolder ) + "\\";
	strFilename = objFS.GetTempName();
	objRS.Save( strTempFolder + strFilename, adPersistXML );
	objTextStream = objFS.OpenTextFile( strTempFolder + strFilename, ForReading );
	Response.Write( objTextStream.ReadAll()	);
	objTextStream.Close();
	
	// NOTE: if you get a Permission Denied message here, you must edit the
	// DACL for your winnt\temp folder to allow IUSR_MACHINENAME and 
	// IWAM_MACHINENAME to be able to delete temporary files created here
	objFS.DeleteFile( strTempFolder + strFilename, false );
}
%>
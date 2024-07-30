// Setup.js (c)1999 John Lam
// Setup Windows Scripting Host script
// This script copies the contents of this directory and any
// child directories to the virtual directory passed in as 
// an argument.
//
// usage: setup.js virtualdirectoryname relativepathtosourcefolder

// Globals
var objShell = new ActiveXObject( "Wscript.Shell" );
var objFSO = new ActiveXObject( "Scripting.FileSystemObject" );
var strVirtualDirectoryName, strPhysicalDirectoryName;
var strSourceDirectoryName;

function displayError( location, e ) {
	WScript.Echo( location + ". Reason: " + e.description );
}

// Recursively copy all of the directories under the specified folder
function walkFolders( objSrcFolder, objDestFolder ) {

	var objSrcFileEnum = new Enumerator( objSrcFolder.Files );
	var objSrcFolderEnum = new Enumerator( objSrcFolder.SubFolders );

	for( ; !objSrcFileEnum.atEnd(); objSrcFileEnum.moveNext() ) {
	
		try {
			var strSourcePath = objSrcFileEnum.item().Path;
			var strDestPath = objDestFolder.Path + "\\" + objSrcFileEnum.item().Name;
			
			objFSO.CopyFile( strSourcePath, 
							 strDestPath );
		}
		catch( e ) {
			displayError( "Copy file: src = " + strSourcePath + ", dest = " + strDestPath,
						  e );
		}
	}
		
	for( ; !objSrcFolderEnum.atEnd(); objSrcFolderEnum.moveNext() ) {
	
		try {
			var strDestFolder = objDestFolder.Path + "\\" + objSrcFolderEnum.item().Name;
			var objChildFolder = objFSO.CreateFolder( strDestFolder );
		}
		catch( e ) {
			displayError( "Create directory: " + strDestFolder,
						  e );
		}
		
		try {
			var objDestFolder = objFSO.GetFolder( strDestFolder );
		}
		catch( e ) {
			displayError( "Get directory: " + strDestFolder,
						  e );
		}
		
		walkFolders( objSrcFolderEnum.item(), 
					 objDestFolder );
	}
}

// Using the ADSI interfaces, find the named web on the computer specified
function findWeb( strComputerName, strWebName ) {

	var objWebSvc, objSiteEnum;

	try {
		objWebSvc = GetObject( "IIS://" + strComputerName + "/W3SVC" );
		objSiteEnum = new Enumerator( objWebSvc );
		
		for( ; !objSiteEnum.atEnd(); objSiteEnum.moveNext() ) {
			if( objSiteEnum.item().Class == "IIsWebServer" && 
				objSiteEnum.item().ServerComment == strWebName )
				return objSiteEnum.item();
		}
	}
	catch( e ) {
		displayError( "findWeb: computer=" + strComputerName + ", web=" + strWebName,
					  e );
	}
	return null;
}

function main() {

	// Setup our environment
	var strWWWRootPath = objShell.RegRead( "HKLM\\Software\\Microsoft\\InetStp\\PathWWWRoot" );

	// Grab the virtual directory name off of the command line
	if( WScript.Arguments.count() != 2 ) {
		WScript.Echo( "usage: setup.js virtualdirectoryname relativepathtosourcefolder\n" );
		return -1;
	}

	strVirtualDirectoryName = WScript.Arguments.item( 0 );
	strPhysicalDirectoryName = strWWWRootPath + "\\" + strVirtualDirectoryName;
	
	// Create the physical directory and abort on error
	try {
		objFSO.CreateFolder( strPhysicalDirectoryName );
	}
	catch( e ) {
		displayError( "Create directory: " + strPhysicalDirectoryName,
					  e );
	}

	// Extract the path to the current directory based on the ScriptFullName property
	var strScriptFullName = new String( WScript.ScriptFullName );
	var nLastIndex = strScriptFullName.lastIndexOf( "\\" );
	var strScriptPath = strScriptFullName.substr( 0, nLastIndex );
	strSourceDirectoryName = strScriptPath + "\\" + WScript.Arguments.item( 1 );
	
	// Copy the files to our new virtual directory
	var objSrcFolder = objFSO.GetFolder( strSourceDirectoryName );
	var objDestFolder = objFSO.GetFolder( strWWWRootPath + "\\" + strVirtualDirectoryName );
	walkFolders( objSrcFolder, objDestFolder );
	
	// Create an application in our new virtual directory
	var objSite = findWeb( "127.0.0.1", "Default Web Site" );	
	if( objSite ) {

		var objApp;
		
		try {
			// This fails with a COM exception
			objApp = objSite.Create( "IIsWebVirtualDir", "Root/" + strVirtualDirectoryName );
		}
		catch( e ) {
			objApp = objSite.GetObject( "IIsWebVirtualDir", "Root/" + strVirtualDirectoryName );
		}
			
		try {
			objApp.Path				= strPhysicalDirectoryName;
			objApp.AccessRead		= true;
			objApp.AccessExecute	= false;
			objApp.AccessScript		= true;
			objApp.SetInfo();
			objApp.AppCreate( true );	// in-proc
			objApp.SetInfo();			// commit
		}
		catch( e ) {
			displayError( "Create Application: " + strVirtualDirectoryName,
						  e );
		}
		
	}
}

main();

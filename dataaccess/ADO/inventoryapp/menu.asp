<%@ Language=VBScript %>
<html>
<head>
<META NAME="GENERATOR" Content="Microsoft Visual Studio 6.0">
</head>
<body>

<link href="main.css" rel="stylesheet" type="text/css">
<table width="100%" background="" bgColor="#d0e3ff" border="0" height="98%" cellSpacing="0">
<tr>
<td vAlign="top">
<table border="0" align="center" background="" cellSpacing="14">
<tr>
    <td align=middle>
    <a href="main.asp" target=main>[Home]</A>
    </td>
</tr>
<tr>
    <td align=middle>
    <br/>
    <a href="inventorylist.asp" target="main">[View All]</A>
    </td>
</tr>
<tr>
    <td align="middle">
    <form action="inventorylist.asp" id="form1" method="post" name="form1" target="main">
          <input id="txtSearch" name="txtSearch" style="HEIGHT: 22px; WIDTH: 107px">
          <br/>
          <input id="submit1" name="submit1" type="submit" value="Search" style="HEIGHT: 24px; WIDTH: 105px">
        </form>
    </td>
</tr>
<tr>
    <td align=middle>
    <br/>
    <a href="http://localhost/VirtualRoot/Template/products.xml?contenttype=text/html" target="main">[View All XML]</A>
    </td>
</tr>
<tr>
    <td align="middle">
    <form action="http://localhost/VirtualRoot/Template/products.xml" id="form1" method="post" name="form1" target="main">
          <input type="hidden" name="contenttype" value="text/html">
          <input id="ProdName" name="ProdName" style="HEIGHT: 22px; WIDTH: 107px">
          <br>
          <input id="submit1" name="submit1" type="submit" value="Search XML" style="HEIGHT: 24px; WIDTH: 105px">
    </form>
    </td>
</tr>
</table>

</td>
</tr>
</table>
</body>
</html>

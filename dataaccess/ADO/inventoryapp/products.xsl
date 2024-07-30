<?xml version='1.0' ?>          
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"  version="1.0">
<xsl:output encoding='iso-8859-1'/>


    <xsl:template match="/">
        <html>
            <head>
                <title>MSDN ADO Product Sample with SQL Server 2000 Features</title>
                <base href="http://localhost/adosamp/inventoryapp/" />
            </head>                
            <body>
                <table border="0" cellPadding="1" cellSpacing="1" width="100%">
                    <tr>
                        <td bgColor="#F0F0F0" width="100%">
                            <strong>
                                <font color="white" size="2">
                                    <a href="inventorydetail.asp">[New...]</a>
                                </font>
                            </strong>
                        </td>
                    </tr>
                </table>
                
                <table border="0" cellPadding="1" cellSpacing="1" width="100%" style="COLOR: black; FONT-FAMILY: Arial; FONT-SIZE: 12pt.;FONT-WEIGHT: 500">
                <tr bgColor="#336699" align="center">
                    <TD><P ><STRONG><FONT color="white" size="2">Product ID:</FONT></STRONG></P></TD>
                    <TD><P ><STRONG><FONT color="white" size="2">Product Name:</FONT></STRONG></P></TD>
                    <TD><P ><STRONG><FONT color="white" size="2">Unit Price:</FONT></STRONG></P></TD>
                    <TD><P ><STRONG><FONT color="white" size="2">Units In Stock:</FONT></STRONG></P></TD>
                    <TD><P ><STRONG><FONT color="white" size="2">Restock Level:</FONT></STRONG></P></TD>
                    <TD><P ><FONT color="white" size="2"><STRONG>Units On Order:</STRONG></FONT></P></TD>
                </tr>
                                
                <xsl:for-each select="root/Products">
                    <tr style="COLOR: black; FONT-FAMILY: Arial; FONT-SIZE: 0.8em; FONT-WEIGHT: 500">
                       <td bgColor="#F0F0F0">
                        <a>
                            <xsl:attribute name="HREF" target="main">inventorydetail.asp?ProductID=<xsl:value-of select="@ProductID"/></xsl:attribute>
                            <xsl:value-of select="@ProductID"/>
                        </a>
                        </td>
                        <td bgColor="#F0F0F0"><xsl:value-of select="@ProductName"/></td>
                        <td bgColor="#F0F0F0"><xsl:value-of select="@UnitPrice"/></td>
                        <td bgColor="#F0F0F0"><xsl:value-of select="@UnitsInStock"/></td>
                        <td bgColor="#F0F0F0"><xsl:value-of select="@ReorderLevel"/></td>
                        <td bgColor="#F0F0F0"><xsl:value-of select="@UnitsOnOrder"/></td>
                    </tr>
                </xsl:for-each>
                </table>
                <TABLE border="0" cellPadding="1" cellSpacing="1" width="100%">
                    <TR>
                        <TD bgColor="#F0F0F0">
                            <STRONG>
                                <FONT color="white" size="2">
                                    <a href="inventorydetail.asp">[New...]</a>
                                </FONT>
                            </STRONG>
                        </TD>
                    </TR>
                </TABLE>
            </body>
         </html>
    </xsl:template>    
</xsl:stylesheet>



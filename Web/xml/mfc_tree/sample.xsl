<xsl:stylesheet xmlns:xsl="http://www.w3.org/TR/WD-xsl">
<xsl:template match="/">
<style>
h1,h2 { color: blue; }
h3 { background-color:#80B0F0; }
body { background-image:url(../_themes/mdcont/modtextb.gif); }
tr { background-color:#C0F0E0;}
</style>
<xsl:apply-templates/>
</xsl:template>

<xsl:template match="textNode()"><xsl:value-of/></xsl:template>
<xsl:template match="*"><xsl:apply-templates/></xsl:template>
		
<xsl:template match="dependencies"><P><font size="-1"><B>Depencencies: </B><blockquote><xsl:apply-templates/></blockquote></font></P></xsl:template>
<xsl:template match="dep"><xsl:value-of/><BR /></xsl:template>
<xsl:template match="author"><P><font size="-1"><B>Published with permission from : </B><xsl:value-of/></font></P></xsl:template>
<xsl:template match="title"><h2><xsl:value-of/></h2></xsl:template>
<xsl:template match="file"><TR valign="top"><xsl:apply-templates/></TR></xsl:template>
<xsl:template match="name"><TD><xsl:value-of/></TD></xsl:template>
<xsl:template match="contains"><TD><xsl:value-of/></TD></xsl:template>
<xsl:template match="mainlist"><h3>Main Files</h3><table width="100%"><xsl:apply-templates/></table></xsl:template>
<xsl:template match="wizlist"><h3>Visual Studio Generated Files</h3><table width="100%"><xsl:apply-templates/></table></xsl:template>

</xsl:stylesheet>
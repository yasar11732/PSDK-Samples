<?xml version="1.0"?>

<!-- Generic stylesheet for viewing XML -->
<xsl:stylesheet xmlns:xsl="http://www.w3.org/TR/WD-xsl">
  <!-- This template will always be executed, even if this stylesheet is not run on the document root -->
  <xsl:template>
    <DIV ID="xmlOutput" STYLE="font-family:Courier; font-size:10pt; margin-bottom:2em">
      <!-- Scoped templates are used so they don't interfere with the "kick-off" template. -->
      <xsl:apply-templates select=".">

        <xsl:template><xsl:apply-templates/></xsl:template>

        <xsl:template match="*">
          <DIV STYLE="margin-left:1em">
            &lt;<xsl:node-name/><xsl:apply-templates select="@*"/>/&gt;
          </DIV>
        </xsl:template>

        <xsl:template match="*[node()]">
          <DIV STYLE="margin-left:1em"><xsl:attribute name="ID"><xsl:eval>this.nodeName</xsl:eval></xsl:attribute>
            <SPAN>&lt;<xsl:node-name/><xsl:apply-templates select="@*"/>&gt;</SPAN><xsl:apply-templates select="node()"/><SPAN>&lt;/<xsl:node-name/>&gt;</SPAN>
          </DIV>
        </xsl:template>

        <xsl:template match="@*">
          <SPAN> <xsl:node-name/>="<SPAN><xsl:value-of /></SPAN>"</SPAN>
        </xsl:template>

        <xsl:template match="pi()">
          <DIV STYLE="margin-left:1em">&lt;?<xsl:node-name/><xsl:apply-templates select="@*"/>?&gt;</DIV>
        </xsl:template>

        <xsl:template match="cdata()"><pre>&lt;![CDATA[<xsl:value-of />]]&gt;</pre></xsl:template>

        <xsl:template match="textNode()"><xsl:value-of /></xsl:template>
    
      </xsl:apply-templates>
    </DIV>
  </xsl:template>
</xsl:stylesheet>
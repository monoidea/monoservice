<?xml version="1.0"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
  <xsl:param name="mediaURL" select="http://monothek.ch/media/monothek-video.mp4"/>
  <xsl:output method="html" encoding="UTF-8" indent="yes"/>

  <xsl:template match="/">
    <xsl:text disable-output-escaping='yes'>&lt;!DOCTYPE html&gt;</xsl:text>
    <html>
      <head>
	<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
	<link rel="stylesheet" type="text/css" href="../style/default.css" />
	<link rel="icon" type="image/png" href="../monoidea.png" />
	<title><xsl:value-of select="/doc-title" /></title>
      </head>
      <body>
	<h1><xsl:value-of select="/title" /></h1>

	<p>
	  <xsl:value-of select="/description" />
	</p>

	<video width="768">
	  <xsl:attribute name="src"><xsl:value-of select="$mediaURL"/></xsl:attribute>
	</video>
	
	<p>
	  <a>
	    <xsl:attribute name="href"><xsl:value-of select="$mediaURL"/></xsl:attribute>
	    <xsl:value-of select="/download" />
	  </a>
	</p>
	
	<p>
	  <xsl:value-of select="/footer" />
	</p>
      </body>
    </html>
    
  </xsl:template>
</xsl:stylesheet>

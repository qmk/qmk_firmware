<!--
             LUFA Library
     Copyright (C) Dean Camera, 2019.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
-->

<!-- Extracts out all function signatures from a combined Doxygen XML output. -->

<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
	<xsl:output method="xml" omit-xml-declaration="yes"/>

	<xsl:template match="doxygen">
		<xsl:for-each select="//memberdef[@kind = 'function']">
			<xsl:value-of select="definition"/><xsl:value-of select="argsstring"/><xsl:text>;&#10;</xsl:text>
		</xsl:for-each>
	</xsl:template>
</xsl:stylesheet>

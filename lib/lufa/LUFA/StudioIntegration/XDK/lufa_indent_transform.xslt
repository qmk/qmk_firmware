<!--
             LUFA Library
     Copyright (C) Dean Camera, 2017.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
-->

<!-- Atmel Studio framework XML transform file -->

<!-- Indents a given XML document to match the node hierarchy. -->
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
	<xsl:output method="xml" omit-xml-declaration="yes" indent="yes"/>

	<!-- Remove all white-space on all elements so that they can be indented -->
	<xsl:strip-space elements="*"/>

	<!-- Match the root node and copy, so that the output will be a correctly
	     indented version of the input document -->
	<xsl:template match="/">
		<xsl:copy-of select="."/>
	</xsl:template>
</xsl:stylesheet>

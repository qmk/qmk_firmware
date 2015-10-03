<!--
             LUFA Library
     Copyright (C) Dean Camera, 2015.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
-->

<!-- Atmel Studio framework VSIX XML transform file -->

<!-- Updates the version element of a Visual Studio VSIX manifest file to the
     value passed as a parameter to the stylesheet transform -->
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:vs="http://schemas.microsoft.com/developer/vsx-schema/2010" version="1.0">
	<xsl:output method="xml" omit-xml-declaration="yes"/>

	<!-- Need to input the extension version for later use -->
	<xsl:param name="extension-version"/>

	<!-- Recursively match and copy/process all nodes/attributes -->
	<xsl:template match="@*|node()">
		<xsl:copy>
			<xsl:apply-templates select="@*|node()"/>
		</xsl:copy>
	</xsl:template>

	<!-- Update the extension version to the version passed as a parameter -->
	<xsl:template match="vs:Version">
		<xsl:copy>
			<xsl:value-of select="$extension-version"/>
		</xsl:copy>
	</xsl:template>

</xsl:stylesheet>

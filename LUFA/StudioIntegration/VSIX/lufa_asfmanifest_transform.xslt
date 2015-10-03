<!--
             LUFA Library
     Copyright (C) Dean Camera, 2015.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
-->

<!-- Atmel Studio framework VSIX XML transform file -->

<!-- Updates an asf-manifest.xml document to add appropriate version
     information. -->
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
	<xsl:output method="xml" omit-xml-declaration="yes"/>

	<!-- Need to input the LUFA version for later use -->
	<xsl:param name="lufa-version"/>

	<!-- Recursively match and copy/process all nodes/attributes -->
	<xsl:template match="@*|node()">
		<xsl:copy>
			<xsl:apply-templates select="@*|node()"/>
		</xsl:copy>
	</xsl:template>

	<!-- Update the LUFA version to the version passed as a parameter -->
	<xsl:template match="Version">
		<xsl:copy>
			<xsl:value-of select="substring($lufa-version, 1, 2)"/>
			<xsl:text>.</xsl:text>
			<xsl:value-of select="substring($lufa-version, 3, 2)"/>
			<xsl:text>.</xsl:text>
			<xsl:value-of select="substring($lufa-version, 5, 2)"/>
		</xsl:copy>
	</xsl:template>
</xsl:stylesheet>

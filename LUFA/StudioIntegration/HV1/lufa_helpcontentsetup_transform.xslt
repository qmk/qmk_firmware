<!--
             LUFA Library
     Copyright (C) Dean Camera, 2013.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
-->

<!-- Atmel Studio HV1 Setup XHTML transform file -->

<!-- Updates a helpcontentsetup.msha document to add appropriate version
     information. -->
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:xhtml="http://www.w3.org/1999/xhtml" version="1.0">
	<xsl:output method="xml" omit-xml-declaration="yes"/>

	<!-- Need to input the LUFA extension version for later use -->
	<xsl:param name="extension-version"/>

	<!-- Recursively match and copy/process all nodes/attributes -->
	<xsl:template match="node()">
		<xsl:copy>
			<xsl:copy-of select="@*"/>
			<xsl:apply-templates select="node()"/>
		</xsl:copy>
	</xsl:template>

	<!-- Update the LUFA version to the version passed as a parameter -->
	<xsl:template match="xhtml:title | xhtml:div[@class='details']/xhtml:span[@class='name']">
		<xsl:copy>
			<xsl:copy-of select="@*"/>

			<xsl:value-of select="."/>
			<xsl:text> (</xsl:text>
			<xsl:value-of select="$extension-version"/>
			<xsl:text>)</xsl:text>
		</xsl:copy>
	</xsl:template>

	<xsl:template match="xhtml:div[@class='package']/xhtml:a">
		<xsl:copy>
			<xsl:copy-of select="@class"/>

			<xsl:attribute name="href">
				<xsl:text>lufa_help_</xsl:text>
				<xsl:value-of select="$extension-version"/>
				<xsl:text>.mshc</xsl:text>
			</xsl:attribute>

			<xsl:text>lufa_help_</xsl:text>
			<xsl:value-of select="$extension-version"/>
			<xsl:text>.mshc</xsl:text>
		</xsl:copy>
	</xsl:template>
</xsl:stylesheet>

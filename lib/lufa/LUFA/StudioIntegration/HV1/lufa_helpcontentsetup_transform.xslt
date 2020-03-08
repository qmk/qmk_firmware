<!--
             LUFA Library
     Copyright (C) Dean Camera, 2019.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
-->

<!-- Atmel Studio HV1 Setup XHTML transform file -->

<!-- Updates a helpcontentsetup.msha document to add appropriate version
     information. -->
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:xhtml="http://www.w3.org/1999/xhtml" version="1.0">
	<xsl:output method="xml" omit-xml-declaration="yes"/>

	<!-- Need to input the LUFA help package filename for later use -->
	<xsl:param name="help-package-filename"/>

	<!-- Recursively match and copy/process all nodes/attributes -->
	<xsl:template match="node()">
		<xsl:copy>
			<xsl:copy-of select="@*"/>
			<xsl:apply-templates select="node()"/>
		</xsl:copy>
	</xsl:template>

	<!-- Update the LUFA help package file name -->
	<xsl:template match="xhtml:div[@class='package']/xhtml:span[@class='name']">
		<xsl:copy>
			<xsl:copy-of select="@class"/>

			<xsl:value-of select="$help-package-filename"/>
		</xsl:copy>
	</xsl:template>

	<xsl:template match="xhtml:div[@class='package']/xhtml:a[@class='current-link']">
		<xsl:copy>
			<xsl:copy-of select="@class"/>

			<xsl:attribute name="href">
				<xsl:value-of select="$help-package-filename"/>
			</xsl:attribute>

			<xsl:value-of select="$help-package-filename"/>
		</xsl:copy>
	</xsl:template>
</xsl:stylesheet>

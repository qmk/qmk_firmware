<!--
             LUFA Library
     Copyright (C) Dean Camera, 2017.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
-->

<!-- Atmel Studio framework Extension XML transform file -->

<!-- Creates an extension.xml document from a given manifest list of XML files,
     and adds appropriate documentation base URI entries and version
     information. -->
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
	<xsl:output method="xml" omit-xml-declaration="yes"/>

	<!-- Store the LUFA version mentioned in the root node for later use -->
	<xsl:param name="lufa-version" select="lufa-manifest/@version"/>

	<!-- Read manifest list and then process all FDK nodes in the referenced
	     document -->
	<xsl:template match="lufa-manifest">
		<xsl:comment>This file has been automatically generated from the LUFA Atmel Studio integration XML files.</xsl:comment>

		<extension-container xmlversion="2.0">
			<xsl:for-each select="xml-source">
				<xsl:apply-templates select="document(@filename)/lufa/extension-container/*"/>
			</xsl:for-each>
		</extension-container>
	</xsl:template>

	<!-- Recursively match and copy/process all nodes/attributes -->
	<xsl:template match="@*|node()">
		<xsl:copy>
			<xsl:apply-templates select="@*|node()"/>
		</xsl:copy>
	</xsl:template>

	<!-- Update the extension version to the version of LUFA being used -->
	<xsl:template match="extension/@version">
		<xsl:attribute name="version">
			<xsl:value-of select="substring($lufa-version, 1, 2)"/>
			<xsl:text>.</xsl:text>
			<xsl:value-of select="substring($lufa-version, 3, 2)"/>
			<xsl:text>.</xsl:text>
			<xsl:value-of select="substring($lufa-version, 5, 2)"/>
		</xsl:attribute>
	</xsl:template>

	<!-- Update the extension online help URLs to the version of LUFA being
	     used -->
	<xsl:template match="online-help/*/@baseurl">
		<xsl:attribute name="baseurl">
			<xsl:value-of select="current()"/>
			<xsl:value-of select="$lufa-version"/>
			<xsl:text>/html/</xsl:text>
		</xsl:attribute>
	</xsl:template>

	<xsl:template match="online-help/index-page/@url">
		<xsl:attribute name="url">
			<xsl:value-of select="current()"/>
			<xsl:value-of select="$lufa-version"/>
			<xsl:text>/html/</xsl:text>
		</xsl:attribute>
	</xsl:template>

</xsl:stylesheet>

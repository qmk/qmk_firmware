<!--
             LUFA Library
     Copyright (C) Dean Camera, 2019.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
-->

<!-- Atmel Studio framework Module XML transform file -->

<!-- Outputs a flat file list of all source files referenced in all modules of
     the input manifest XML file, so that they can be checked for existence. -->
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
	<xsl:output method="xml" omit-xml-declaration="yes"/>

	<!-- Read manifest list, add a comment to indicate the source filename
	     and then process all ASF nodes in the referenced document -->
	<xsl:template match="lufa-manifest">
		<xsl:for-each select="xml-source">
			<xsl:comment>Sourced from <xsl:value-of select="@filename"/></xsl:comment>
			<xsl:apply-templates select="document(@filename)/lufa/asf/*"/>
		</xsl:for-each>
	</xsl:template>

	<!-- Recursively match and process all nodes/attributes -->
	<xsl:template match="@*|node()">
		<xsl:apply-templates select="@*|node()"/>
	</xsl:template>

	<!-- Match source file nodes, output filename -->
	<xsl:template match="build[@type='c-source']|build[@type='header-file']|build[@type='distribute']">
		<xsl:value-of select="@value"/>
		<xsl:text>&#xA;</xsl:text>
	</xsl:template>
</xsl:stylesheet>

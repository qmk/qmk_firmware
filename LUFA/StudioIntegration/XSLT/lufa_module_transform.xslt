<!--
             LUFA Library
     Copyright (C) Dean Camera, 2013.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
-->

<!-- Atmel Studio framework Module XML transform file -->

<!-- Creates an asf.xml module document from a given manifest list of XML files,
     and adds appropriate documentation links by cross-referencing the Doxygen
     tag output file to map Doxygen group names to generated filenames. -->
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
	<xsl:output method="xml" omit-xml-declaration="yes"/>

	<!-- Store the LUFA Doxygen tag filename mentioned in the root node for later use -->
	<xsl:param name="lufa-doxygen-tagfile" select="lufa-manifest/@tagfile"/>

	<!-- Read manifest list, add a comment to indicate the source filename
	     and then copy/process all ASF nodes in the referenced document -->
	<xsl:template match="lufa-manifest">
		<xsl:comment>This file has been automatically generated from the LUFA Atmel Studio integration XML files.</xsl:comment>

		<asf xmlversion="1.0">
			<xsl:for-each select="xml-source">
				<xsl:comment>Sourced from <xsl:value-of select="@filename"/></xsl:comment>
				<xsl:apply-templates select="document(@filename)/lufa/asf/*"/>
			</xsl:for-each>
		</asf>
	</xsl:template>

	<!-- Recursively match and copy/process all nodes/attributes -->
	<xsl:template match="@*|node()">
		<xsl:copy>
			<xsl:apply-templates select="@*|node()"/>
		</xsl:copy>
	</xsl:template>

	<!-- For Doxygen entry point nodes we need to convert them into help link
	     nodes instead, so that they show up as links in Studio correctly -->
	<xsl:template match="build[@type='doxygen-entry-point']">
		<xsl:call-template name="add_help_nodes">
		    <xsl:with-param name="filename" select="document($lufa-doxygen-tagfile)//compound[name=current()/@value]/filename"/>
		</xsl:call-template>
	</xsl:template>

	<!-- Generate additional help nodes from the given help filename -->
	<xsl:template name="add_help_nodes">
		<xsl:param name="filename"/>

		<build type="online-help" subtype="module-help-page-append">
		 	<xsl:attribute name="value">
			    <xsl:value-of select="$filename"/>
  			</xsl:attribute>
  		</build>
	</xsl:template>

</xsl:stylesheet>

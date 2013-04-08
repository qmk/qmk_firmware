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

	<!-- Store the LUFA Doxygen documentation filename mentioned in the root node for later use -->
	<xsl:param name="lufa-doxygen-docfile" select="lufa-manifest/@docfile"/>

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
	     nodes instead and add descriptions, so that they show up as links in
	     Studio correctly -->
	<xsl:template match="build[@type='doxygen-entry-point']">
		<build type="online-help" subtype="module-help-page-append">
		 	<xsl:attribute name="value">
		 		<!-- Extract filename of the HTML file that contains the documentation for this module from the Doxgen tag file -->
			    <xsl:value-of select="document($lufa-doxygen-tagfile)/tagfile/compound[name=current()/@value]/filename"/>
  			</xsl:attribute>
  		</build>

		<info type="description" value="summary">
		 	<!-- Extract brief description of the module from the Doxygen combined XML documentation file -->
			<xsl:value-of select="document($lufa-doxygen-docfile)/doxygen/compounddef[compoundname=current()/@value]/briefdescription/para"/>
		</info>
	</xsl:template>

</xsl:stylesheet>

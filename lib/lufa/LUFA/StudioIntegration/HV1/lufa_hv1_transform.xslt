<!--
             LUFA Library
     Copyright (C) Dean Camera, 2017.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
-->

<!-- Docbook XML to Microsoft Help Viewer 1.0 transform file -->

<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

	<xsl:import href="../Docbook/mshelp/docbook.xsl"/>

	<xsl:output method="xml" indent="no"/>

	<xsl:template match="emphasis[@role = 'keyword' or @role = 'keywordtype' or @role = 'keywordflow']">
		<span class="hl-keyword" style="color: #0079C1">
			<xsl:apply-templates/>
		</span>
	</xsl:template>

	<xsl:template match="emphasis[@role = 'stringliteral' or @role = 'charliteral']">
		<span class="hl-string" style="color: #800000">
			<xsl:apply-templates/>
		</span>
	</xsl:template>

	<xsl:template match="emphasis[@role = 'comment']">
		<em class="hl-comment" style="color: #008000">
			<xsl:apply-templates/>
		</em>
	</xsl:template>

	<xsl:template match="emphasis[@role = 'preprocessor']">
		<span class="hl-preprocessor" style="color: #A000A0">
			<xsl:apply-templates/>
		</span>
	</xsl:template>

	<xsl:template match="emphasis[@role = 'normal' and ancestor::programlisting]">
		<xsl:apply-templates />
	</xsl:template>

</xsl:stylesheet>

<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet 
    xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
    xmlns:d="http://docbook.org/ns/docbook"
	xmlns="http://www.w3.org/1999/xhtml"
    exclude-result-prefixes="xsl d"   
    version="1.0">

	<xsl:import href="../xhtml/chunk.xsl"/>
	<xsl:import href="../xhtml/highlight.xsl"/>
	
	<!-- 
		Based on the normal xhtml templates, all overrides applicable to 
		xhtml is applicable to HV1.
	-->
	
	<xsl:import href="hv1-common.xsl"/>

	<!-- 
		Choose if links should be generated using ms-xhelp (default) or 
		the more verbose ms.help type. The latter requires product.name, 
		product.version and product.locale to be set
	-->
	<xsl:param name="use.mshelp.links" select="0"/>
	
	<!-- 
		Name of target product. If specified then each page is 
		marked with this product. This is usualy set during 
		install time.
	-->
	<xsl:param name="product.name" select="''" />
	
	<!-- 
		Name of target version. If specified then each page is 
		marked with this version. This is usualy set during 
		install time.
	-->
	<xsl:param name="product.version" select="''" />
	
	<!-- 
		Locale for the help. Should always be set
	-->
	<xsl:param name="product.locale" select="'en-US'" />
	
	<!-- 
		Self branding. Gives access for chunks to load 
		it's own branding package during runtime
	-->
	<xsl:param name="topic.selfbrand" select="1"/>


	<!-- Use doctitle for olinks -->
	<xsl:param name="olink.doctitle" select="'yes'" />

	<!-- Enable source code highlighting-->
	<xsl:param name="highlight.source" select="1"/>
	
</xsl:stylesheet>

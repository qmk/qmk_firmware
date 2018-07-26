<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
				xmlns:d="http://docbook.org/ns/docbook"
				xmlns="http://www.w3.org/1999/xhtml"
				exclude-result-prefixes="d"
    			version="1.0">


	<!-- no separate HTML page with index as this is binary in hv1 -->
	<xsl:param name="generate.index" select="0"/>


	<!-- Generate help tags in header -->
	<xsl:template name="user.head.content">
		<xsl:param name="node" select="''" />
		<xsl:variable name="up" select="parent::*"/>

		<!-- Locale should be first Help tag-->
		<meta name="Microsoft.Help.Locale">
			<xsl:attribute name="content">
				<xsl:choose>
					<xsl:when test="$product.locale and product.locale != ''">
						<xsl:value-of select="$product.locale"/>
					</xsl:when>
					<xsl:otherwise>
						<xsl:text>en-US</xsl:text>
					</xsl:otherwise>
				</xsl:choose>
			</xsl:attribute>
		</meta>

		<!-- Specify locale for this chunk. Should probably query xml:lang -->
		<meta name="Microsoft.Help.TopicLocale">
			<xsl:attribute name="content">
				<xsl:choose>
					<xsl:when test="@xml:lang">
						<xsl:value-of select="@xml:lang"/>
					</xsl:when>
					<xsl:when test="$product.locale and product.locale != ''">
						<xsl:value-of select="$product.locale"/>
					</xsl:when>
					<xsl:otherwise>
						<xsl:text>en-US</xsl:text>
					</xsl:otherwise>
				</xsl:choose>
			</xsl:attribute>
		</meta>

		<!-- This is the unique ID for this page -->
		<meta name="Microsoft.Help.Id">
			<xsl:attribute name="content">
				<xsl:call-template name="hv1.toc.id"/>
			</xsl:attribute>
		</meta>

		<!-- The ID of the parent TOC node (-1 is root) -->
		<meta name="Microsoft.Help.TocParent">
			<xsl:attribute name="content">
				<xsl:call-template name="hv1.toc.parent.id">
					<xsl:with-param name="up" select="$up"/>
				</xsl:call-template>
			</xsl:attribute>
		</meta>

		<!-- For all pages with the same parent, the order is set by TocOrder -->
		<meta name="Microsoft.Help.TocOrder">
			<xsl:attribute name="content">
				<xsl:value-of select="1+count(preceding-sibling::chapter|preceding-sibling::section)"/>
			</xsl:attribute>
		</meta>

		<!-- boolean to indicate if this page is allowed to load custom branding -->
		<meta name="Microsoft.Help.SelfBranded">
			<xsl:attribute name="content">
				<xsl:choose>
					<xsl:when test="$topic.selfbrand">
						<xsl:text>true</xsl:text>
					</xsl:when>
					<xsl:otherwise>
						<xsl:text>false</xsl:text>
					</xsl:otherwise>
				</xsl:choose>
			</xsl:attribute>
		</meta>

		<!--
			Insert description meta element. This is shown in searches and indexes
		-->

		<xsl:variable name="description">
			<xsl:call-template name="hv1.description"/>
		</xsl:variable>
		<xsl:if test="$description != ''">
			<meta name="Description">
				<xsl:attribute name="content">
					<xsl:call-template name="hv1.description"/>
				</xsl:attribute>
			</meta>
		</xsl:if>

		<!-- Display version of page -->
		<xsl:variable name="display.version">
			<xsl:call-template name="hv1.display.version"/>
		</xsl:variable>
		<xsl:if test="$display.version != ''">
			<meta name="Microsoft.Help.DisplayVersion">
				<xsl:attribute name="content">
					<xsl:value-of select="$display.version"/>
				</xsl:attribute>
			</meta>
		</xsl:if>

		<!--
			Content type is used to distinguish between multiple topics with same id.
			Usualy to have multiple versions available
		-->
		<!--
		<meta name="Microsoft.Help.ContentType">
			<xsl:attribute name="content">
				TODO: implement
			</xsl:attribute>
		</meta>
		-->


		<!-- If a product name is given, then mark each header with this name-->
		<xsl:if test="$product.name and $product.name != ''">
			<meta name="Microsoft.Help.Product">
				<xsl:attribute name="content">
					<xsl:value-of select="$product.name"/>
				</xsl:attribute>
			</meta>
		</xsl:if>

		<!-- If a version is given, then mark each header with version-->
		<xsl:if test="$product.version and $product.version != ''">
			<meta name="Microsoft.Help.ProductVersion">
				<xsl:attribute name="content">
					<xsl:value-of select="$product.version"/>
				</xsl:attribute>
			</meta>
		</xsl:if>

		<!--
			Insert all keywords for this chunk. These are used
			by the help runtime to generate indexes and refine search
		-->
		<xsl:call-template name="hv1.keywords" />

		<!--
			Insert all F1 ids for this chunk. This is used
			by the help runtime to resolve F1 queries
		-->
		<xsl:call-template name="hv1.f1" />
	</xsl:template>


	<!-- There are links from ToC pane to bibliodivs, so there must be anchor -->
	<xsl:template match="bibliodiv/title">
		<h3 class="{name(.)}">
			<xsl:call-template name="anchor">
				<xsl:with-param name="node" select=".."/>
				<xsl:with-param name="conditional" select="0"/>
			</xsl:call-template>
			<xsl:apply-templates/>
		</h3>
	</xsl:template>

	<!--
		Template to get a page id.

		Needs to be unique in the target help system; microsoft uses UUIDs for this.
		To avoid UUIDs and generate-id (only unique in current xml fragment),
		we do
			<root.filename> +
				<last ancestor title> +
					<second last ancestor title> +
						....
						<self title>, 	where different types of sections/fragments
											may be prefixed with a type identifier.

		This should generate a fairly specific/unique ID.
		-->
	<xsl:template name="get.id.from.pagename">
		<xsl:param name="target" />
		<xsl:value-of select="$root.filename"/>
		<xsl:variable name="id.of.document">
			<xsl:apply-templates select="$target" mode="recursive-chunk-id"/>
		</xsl:variable>
		<xsl:variable name="titleWithSpace">
			<xsl:value-of select="key('id',$id.of.document)/title"/>
		</xsl:variable>
		<xsl:value-of select="translate($id.of.document,' ','')" />
	</xsl:template>

	<!-- template that returns the page id used above -->
	<xsl:template match="*" mode="recursive-chunk-id">
		<xsl:param name="recursive" select="false()"/>

		<!-- returns the filename of a chunk -->
		<xsl:variable name="ischunk">
			<xsl:call-template name="chunk"/>
		</xsl:variable>

		<xsl:variable name="dbhtml-filename">
			<xsl:call-template name="pi.dbhtml_filename"/>
		</xsl:variable>

		<xsl:variable name="filename">
			<xsl:choose>
				<xsl:when test="$dbhtml-filename != ''">
					<xsl:value-of select="$dbhtml-filename"/>
				</xsl:when>
				<!-- if this is the root element, use the root.filename -->
				<xsl:when test="not(parent::*) and $root.filename != ''">
					<xsl:value-of select="$root.filename"/>
					<!-- <xsl:value-of select="$html.ext"/> -->
				</xsl:when>
				<!-- Special case -->
				<xsl:when test="self::legalnotice and not($generate.legalnotice.link = 0)">
					<xsl:choose>
						<xsl:when test="(@id or @xml:id) and not($use.id.as.filename = 0)">
							<!-- * if this legalnotice has an ID, then go ahead and use -->
							<!-- * just the value of that ID as the basename for the file -->
							<!-- * (that is, without prepending an "ln-" too it) -->
							<xsl:value-of select="(@id|@xml:id)[1]"/>
							<!-- <xsl:value-of select="$html.ext"/>-->
						</xsl:when>
						<xsl:otherwise>
							<!-- * otherwise, if this legalnotice does not have an ID, -->
							<!-- * then we generate an ID... -->
							<xsl:variable name="id">
								<xsl:call-template name="object.id"/>
							</xsl:variable>
							<!-- * ...and then we take that generated ID, prepend an -->
							<!-- * "ln-" to it, and use that as the basename for the file -->
							<!-- <xsl:value-of select="concat('ln-',$id,$html.ext)"/>-->
						</xsl:otherwise>
					</xsl:choose>
				</xsl:when>
				<!-- if there's no dbhtml filename, and if we're to use IDs as -->
				<!-- filenames, then use the ID to generate the filename. -->
				<xsl:when test="(@id or @xml:id) and $use.id.as.filename != 0">
					<xsl:value-of select="(@id|@xml:id)[1]"/>
					<!-- <xsl:value-of select="$html.ext"/>-->
				</xsl:when>
				<xsl:otherwise/>
			</xsl:choose>
		</xsl:variable>

		<xsl:choose>
			<xsl:when test="$ischunk='0'">
				<!-- if called on something that isn't a chunk, walk up... -->
				<xsl:choose>
					<xsl:when test="count(parent::*)&gt;0">
						<xsl:apply-templates mode="recursive-chunk-id" select="parent::*">
							<xsl:with-param name="recursive" select="$recursive"/>
						</xsl:apply-templates>
					</xsl:when>
					<!-- unless there is no up, in which case return "" -->
					<xsl:otherwise/>
				</xsl:choose>
			</xsl:when>

			<xsl:when test="not($recursive) and $filename != ''">
				<!-- if this chunk has an explicit name, use it -->
				<xsl:value-of select="$filename"/>
			</xsl:when>

			<xsl:when test="self::set">
				<xsl:value-of select="$root.filename"/>
			</xsl:when>

			<xsl:when test="self::book">
				<xsl:text>bk</xsl:text>
				<xsl:number level="any" format="01"/>
			</xsl:when>

			<xsl:when test="self::article">
				<xsl:if test="/set">
					<!-- in a set, make sure we inherit the right book info... -->
					<xsl:apply-templates mode="recursive-chunk-id" select="parent::*">
						<xsl:with-param name="recursive" select="true()"/>
					</xsl:apply-templates>
				</xsl:if>

				<xsl:text>ar</xsl:text>
				<xsl:number level="any" format="01" from="book"/>
			</xsl:when>

			<xsl:when test="self::preface">
				<xsl:if test="/set">
					<!-- in a set, make sure we inherit the right book info... -->
					<xsl:apply-templates mode="recursive-chunk-id" select="parent::*">
						<xsl:with-param name="recursive" select="true()"/>
					</xsl:apply-templates>
				</xsl:if>

				<xsl:text>pr</xsl:text>
				<xsl:number level="any" format="01" from="book"/>
			</xsl:when>

			<xsl:when test="self::chapter">
				<xsl:if test="/set">
					<!-- in a set, make sure we inherit the right book info... -->
					<xsl:apply-templates mode="recursive-chunk-id" select="parent::*">
						<xsl:with-param name="recursive" select="true()"/>
					</xsl:apply-templates>
				</xsl:if>

				<xsl:text>ch</xsl:text>
				<xsl:number level="any" format="01" from="book"/>
			</xsl:when>

			<xsl:when test="self::appendix">
				<xsl:if test="/set">
					<!-- in a set, make sure we inherit the right book info... -->
					<xsl:apply-templates mode="recursive-chunk-id" select="parent::*">
						<xsl:with-param name="recursive" select="true()"/>
					</xsl:apply-templates>
				</xsl:if>

				<xsl:text>ap</xsl:text>
				<xsl:number level="any" format="a" from="book"/>
			</xsl:when>

			<xsl:when test="self::part">
				<xsl:choose>
					<xsl:when test="/set">
						<!-- in a set, make sure we inherit the right book info... -->
						<xsl:apply-templates mode="recursive-chunk-id" select="parent::*">
							<xsl:with-param name="recursive" select="true()"/>
						</xsl:apply-templates>
					</xsl:when>
					<xsl:otherwise>
					</xsl:otherwise>
				</xsl:choose>

				<xsl:text>pt</xsl:text>
				<xsl:number level="any" format="01" from="book"/>
			</xsl:when>

			<xsl:when test="self::reference">
				<xsl:choose>
					<xsl:when test="/set">
						<!-- in a set, make sure we inherit the right book info... -->
						<xsl:apply-templates mode="recursive-chunk-id" select="parent::*">
							<xsl:with-param name="recursive" select="true()"/>
						</xsl:apply-templates>
					</xsl:when>
					<xsl:otherwise>
					</xsl:otherwise>
				</xsl:choose>

				<xsl:text>rn</xsl:text>
				<xsl:number level="any" format="01" from="book"/>
			</xsl:when>

			<xsl:when test="self::refentry">
				<xsl:choose>
					<xsl:when test="parent::reference">
						<xsl:apply-templates mode="recursive-chunk-id" select="parent::*">
							<xsl:with-param name="recursive" select="true()"/>
						</xsl:apply-templates>
					</xsl:when>
					<xsl:otherwise>
					</xsl:otherwise>
				</xsl:choose>

				<xsl:text>re</xsl:text>
				<xsl:number level="any" format="01" from="book"/>
			</xsl:when>

			<xsl:when test="self::colophon">
				<xsl:choose>
					<xsl:when test="/set">
						<!-- in a set, make sure we inherit the right book info... -->
						<xsl:apply-templates mode="recursive-chunk-id" select="parent::*">
							<xsl:with-param name="recursive" select="true()"/>
						</xsl:apply-templates>
					</xsl:when>
					<xsl:otherwise>
					</xsl:otherwise>
				</xsl:choose>

				<xsl:text>co</xsl:text>
				<xsl:number level="any" format="01" from="book"/>
			</xsl:when>

			<xsl:when test="self::sect1
									or self::sect2
									or self::sect3
									or self::sect4
									or self::sect5
									or self::section">
				<xsl:apply-templates mode="recursive-chunk-id" select="parent::*">
					<xsl:with-param name="recursive" select="true()"/>
				</xsl:apply-templates>
				<xsl:text>s</xsl:text>
				<xsl:number format="01"/>
			</xsl:when>

			<xsl:when test="self::bibliography">
				<xsl:choose>
					<xsl:when test="/set">
						<!-- in a set, make sure we inherit the right book info... -->
						<xsl:apply-templates mode="recursive-chunk-id" select="parent::*">
							<xsl:with-param name="recursive" select="true()"/>
						</xsl:apply-templates>
					</xsl:when>
					<xsl:otherwise>
					</xsl:otherwise>
				</xsl:choose>

				<xsl:text>bi</xsl:text>
				<xsl:number level="any" format="01" from="book"/>
			</xsl:when>

			<xsl:when test="self::glossary">
				<xsl:choose>
					<xsl:when test="/set">
						<!-- in a set, make sure we inherit the right book info... -->
						<xsl:apply-templates mode="recursive-chunk-id" select="parent::*">
							<xsl:with-param name="recursive" select="true()"/>
						</xsl:apply-templates>
					</xsl:when>
					<xsl:otherwise>
					</xsl:otherwise>
				</xsl:choose>

				<xsl:text>go</xsl:text>
				<xsl:number level="any" format="01" from="book"/>
			</xsl:when>

			<xsl:when test="self::index">
				<xsl:choose>
					<xsl:when test="/set">
						<!-- in a set, make sure we inherit the right book info... -->
						<xsl:apply-templates mode="recursive-chunk-id" select="parent::*">
							<xsl:with-param name="recursive" select="true()"/>
						</xsl:apply-templates>
					</xsl:when>
					<xsl:otherwise>
					</xsl:otherwise>
				</xsl:choose>

				<xsl:text>ix</xsl:text>
				<xsl:number level="any" format="01" from="book"/>
			</xsl:when>

			<xsl:when test="self::setindex">
				<xsl:text>si</xsl:text>
				<xsl:number level="any" format="01" from="set"/>
			</xsl:when>

			<xsl:otherwise>
				<xsl:text>chunk-filename-error-</xsl:text>
				<xsl:value-of select="name(.)"/>
				<xsl:number level="any" format="01" from="set"/>
			</xsl:otherwise>
		</xsl:choose>
	</xsl:template>

	<!-- Main template that generates internal links -->
	<xsl:template name="href.target">
		<xsl:param name="context" select="."/>
		<xsl:param name="object" select="."/>
		<xsl:param name="toc-context" select="."/>

		<xsl:variable name="id">
			<xsl:call-template name="get.id.from.pagename">
				<xsl:with-param name="target" select="$object"/>
			</xsl:call-template>
		</xsl:variable>

		<xsl:variable name="href">
			<xsl:choose>
				<xsl:when test="$use.mshelp.links">
					<!-- Generate a ms.help type link-->
					<xsl:if test="$product.name = ''">
						<xsl:message terminate="yes">
							$product.name needs to be set to generate ms.help style links
						</xsl:message>
					</xsl:if>
					<xsl:if test="$product.version = ''">
						<xsl:message terminate="yes">
							$product.version needs to be set to generate ms.help style links
						</xsl:message>
					</xsl:if>
					<xsl:if test="$product.locale = ''">
						<xsl:message terminate="yes">
							$product.locale needs to be set to generate ms.help style links
						</xsl:message>
					</xsl:if>

					<xsl:text>ms.help?method=page&amp;id=</xsl:text>
					<xsl:value-of select="$id"/>
					<xsl:text>&amp;product=</xsl:text>
					<xsl:value-of select="$product.name"/>
					<xsl:text>&amp;productVersion=</xsl:text>
					<xsl:value-of select="$product.version"/>
					<xsl:text>&amp;locale=</xsl:text>
					<xsl:value-of select="$product.locale"/>
					<!-- Append the jump id if the current object has an id-->
					<xsl:if test="$object[@id or @xml:id]">
						<xsl:text>#</xsl:text>
						<xsl:value-of select="$object/@id|$object/@xml:id"/>
					</xsl:if>
				</xsl:when>
				<xsl:otherwise>
					<!-- Generate ms-xhelp type links. Default-->
					<xsl:text>ms-xhelp:///?Id=</xsl:text>
					<xsl:value-of select="$id"/>
				</xsl:otherwise>
			</xsl:choose>
		</xsl:variable>
		<xsl:value-of select="$href"/>
	</xsl:template>

	<xsl:template match="*" mode="common.html.attributes">
		<xsl:param name="class" select="local-name(.)"/>
		<xsl:param name="inherit" select="0"/>

		<!--
			Workaround for known issue with HelpLibAgent
			Comment from Bruce Belson:
			<pre> tags get their whitespace mangled by the Help Library Agent,
			unless the non-standard attribute xml:space="preserve" is added to the pre element.
		-->
		<xsl:if test="$class = 'programlisting' or $class = 'verbatim' or $class = 'litterallayout' or $class = 'screen'">
			<xsl:attribute name="xml:space">preserve</xsl:attribute>
		</xsl:if>

		<xsl:call-template name="generate.html.lang"/>
		<xsl:call-template name="dir">
			<xsl:with-param name="inherit" select="$inherit"/>
		</xsl:call-template>
		<xsl:apply-templates select="." mode="class.attribute">
			<xsl:with-param name="class" select="$class"/>
		</xsl:apply-templates>
	</xsl:template>


	<xsl:template name="hv1.display.version">
		<xsl:apply-templates mode="title.markup" select="ancestor-or-self::book"/>
		<xsl:if test="ancestor-or-self::chapter">
			<xsl:text> - </xsl:text>
			<xsl:apply-templates mode="title.markup" select="ancestor-or-self::chapter"/>
		</xsl:if>
	</xsl:template>


	<!-- Generate a meta element for each keyword in chunk -->
	<xsl:template name="hv1.keywords">
		<xsl:variable name="is.chunk">
			<xsl:call-template name="chunk">
				<xsl:with-param name="node" select="."/>
			</xsl:call-template>
		</xsl:variable>

		<xsl:for-each select=".//indexterm[$is.chunk = '0'] |
			(./indexterm | *[not(self::section or self::preface or self::book or self::chapter)]//indexterm)[$is.chunk = '1']">
			<xsl:choose>
				<xsl:when test="primary != ''">
					<meta name="Microsoft.Help.Keywords">
						<xsl:attribute name="content">
							<xsl:choose>
								<!-- This concats the primary and secondary togheter, separated by colon if there exists
								a tertiary element -->
								<xsl:when test="tertiary">
									<xsl:value-of select="primary/text()" />
									<xsl:text>: </xsl:text>
									<xsl:value-of select="secondary/text()" />
									<xsl:text>, </xsl:text>
									<xsl:value-of select="tertiary/text()" />
								</xsl:when>

								<xsl:otherwise>
									<xsl:for-each select="primary/text() | secondary/text()">
										<xsl:value-of select="." />
										<xsl:if test="not(position() = last())">, </xsl:if>
									</xsl:for-each>
								</xsl:otherwise>
							</xsl:choose>
						</xsl:attribute>
					</meta>
				</xsl:when>
				<xsl:otherwise/>
			</xsl:choose>
		</xsl:for-each>
	</xsl:template>

	<!-- Generate a F1 meta element for each indexterm with an ID (used as F1 id) -->
	<xsl:template name="hv1.f1">
		<xsl:variable name="is.chunk">
			<xsl:call-template name="chunk">
				<xsl:with-param name="node" select="."/>
			</xsl:call-template>
		</xsl:variable>

		<xsl:variable name="id">
			<xsl:call-template name="hv1.toc.id"/>
		</xsl:variable>

		<xsl:for-each select=".//indexterm[$is.chunk = '0'] |
			(./indexterm | *[not(self::section or self::preface or self::book or self::chapter)]//indexterm)[$is.chunk = '1']">
			<xsl:if test="@id|@xml:id">
				<meta name="Microsoft.Help.F1">
					<xsl:attribute name="content">
						<xsl:value-of select="(@id|@xml:id)[1]" />
					</xsl:attribute>
				</meta>
			</xsl:if>
		</xsl:for-each>
	</xsl:template>

	<!-- ID used for to resolution. Using default ID -->
	<xsl:template name="hv1.toc.id">
		<xsl:variable name="href">
			<xsl:call-template name="get.id.from.pagename">
				<xsl:with-param name="target" select="."/>
			</xsl:call-template>
		</xsl:variable>
		<xsl:value-of select="$href"/>
	</xsl:template>

	<!-- Determine parent id (if top level -> -1) -->
	<xsl:template name="hv1.toc.parent.id">
		<xsl:param name="up" select="''"/>
		<xsl:variable name="href">
			<xsl:choose>
				<xsl:when test="$up">
					<!-- I have a parent -->
					<xsl:call-template name="get.id.from.pagename">
						<xsl:with-param name="target" select="$up"/>
					</xsl:call-template>
				</xsl:when>
				<xsl:otherwise>
					<xsl:text>-1</xsl:text>
				</xsl:otherwise>
			</xsl:choose>
		</xsl:variable>
		<xsl:value-of select="$href"/>
	</xsl:template>

	<xsl:template name="hv1.description">
		<xsl:variable name="content">
			<xsl:choose>
				<xsl:when test="abstract|d:abstract|d:info/d:abstract|bookinfo/abstract|sectioninfo/abstract|articleinfo/abstract|partinfo/abstract">
					<xsl:value-of select="(abstract|d:abstract|d:info/d:abstract|bookinfo/abstract|sectioninfo/abstract|articleinfo/abstract|partinfo/abstract)[1]"/>
				</xsl:when>
				<xsl:when test="child::para">
					<xsl:value-of select="substring(normalize-space(child::para[1]), 0, 150)"/>
				</xsl:when>
				<xsl:otherwise/>
			</xsl:choose>
		</xsl:variable>
		<xsl:if test="$content != ''">
			<xsl:value-of select="concat($content, '...')"/>
		</xsl:if>
	</xsl:template>


</xsl:stylesheet>

<?xml version="1.0" encoding="UTF-8"?>

<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

	<xsl:output method="xml" indent="no"/>

	<xsl:param name="keyword.namespace" select="'Atmel.Language.C'"/>

	<xsl:template name="generate.book.title">
		<xsl:text>LUFA Library</xsl:text>
	</xsl:template>

	<xsl:template name="generate.book.id">
		<xsl:param name="book.title"/>
		<xsl:choose>
			<xsl:when test="@id">
				<xsl:value-of select="@id"/>
			</xsl:when>
			<xsl:otherwise>
				<xsl:value-of select="translate($book.title, ' ','')"/>
			</xsl:otherwise>
		</xsl:choose>
	</xsl:template>

	<xsl:template name="generate.index.id">
		<xsl:param name="name"/>
		<xsl:variable name="book.title">
			<xsl:call-template name="generate.book.title"/>
		</xsl:variable>
		<xsl:variable name="book.id">
			<xsl:call-template name="generate.book.id">
				<xsl:with-param name="book.title" select="$book.title"/>
			</xsl:call-template>
		</xsl:variable>

		<indexterm id="{$keyword.namespace}.{$name}">
			<primary>
				<xsl:value-of select="$book.title"/>
			</primary>
			<secondary>
				<xsl:value-of select="$name"/>
			</secondary>
		</indexterm>
	</xsl:template>

	<xsl:template match="doxygen">
		<xsl:variable name="book.title">
			<xsl:call-template name="generate.book.title"/>
		</xsl:variable>

		<xsl:variable name="book.id">
			<xsl:call-template name="generate.book.id">
				<xsl:with-param name="book.title" select="$book.title"/>
			</xsl:call-template>
		</xsl:variable>

		<book id="{$book.id}">
			<title>
				<xsl:value-of select="$book.title"/>
			</title>

			<!-- Add index chapter -->
			<xsl:apply-templates select="compounddef[@kind = 'page' and @id = 'indexpage']">
				<xsl:with-param name="element.type" select="'chapter'"/>
				<xsl:with-param name="page.title"   select="'Library Information'"/>
			</xsl:apply-templates>

			<!-- Add free-floating chapters -->
			<xsl:apply-templates select="compounddef[@kind = 'page' and not(@id = 'indexpage') and not(//innerpage/@refid = @id)]">
				<xsl:with-param name="element.type" select="'chapter'"/>
			</xsl:apply-templates>

			<!-- Add Modules chapter -->
			<chapter>
				<title>Modules</title>
				<xsl:apply-templates select="compounddef[@kind = 'group' and not(//innergroup/@refid = @id)]"/>
			</chapter>
		</book>
	</xsl:template>

	<xsl:template match="compounddef[@kind = 'page']">
		<xsl:param name="element.type" select="'section'"/>
		<xsl:param name="page.title"   select="title"/>

		<xsl:element name="{$element.type}">
			<xsl:attribute name="id">
				<xsl:value-of select="@id"/>
			</xsl:attribute>

			<xsl:variable name="name">
				<xsl:text>LUFA.</xsl:text>
				<xsl:value-of select="translate(compoundname, '_', '.')"/>
			</xsl:variable>

			<xsl:call-template name="generate.index.id">
				<xsl:with-param name="name" select="$name"/>
			</xsl:call-template>

			<title>
				<xsl:value-of select="$page.title"/>
			</title>

			<xsl:apply-templates select="detaileddescription"/>

			<xsl:if test="not(innerpage) and count(detaileddescription//sect1)">
				<para>
					<emphasis role="bold">Subsections:</emphasis>
					<itemizedlist>
						<xsl:for-each select="detaileddescription//sect1">
							<listitem>
								<link linkend="{@id}">
									<xsl:value-of select="title"/>
								</link>
							</listitem>
						</xsl:for-each>
					</itemizedlist>
				</para>
			</xsl:if>

			<xsl:for-each select="innerpage">
				<xsl:apply-templates select="ancestor::*/compounddef[@kind = 'page' and @id = current()/@refid]"/>
			</xsl:for-each>
		</xsl:element>
	</xsl:template>

	<xsl:template match="compounddef[@kind = 'group']">
		<section id="{@id}">
			<title>
				<xsl:value-of select="title"/>
			</title>

			<xsl:variable name="name">
				<xsl:text>LUFA.</xsl:text>
				<xsl:value-of select="translate(compoundname, '_', '.')"/>
			</xsl:variable>

			<xsl:call-template name="generate.index.id">
				<xsl:with-param name="name" select="$name"/>
			</xsl:call-template>

			<xsl:apply-templates select="detaileddescription"/>

			<xsl:if test="count(innergroup)">
				<para>
					<emphasis role="bold">Subgroups:</emphasis>
					<itemizedlist>
						<xsl:for-each select="innergroup">
							<listitem>
								<link linkend="{@refid}">
									<xsl:value-of select="text()"/>
								</link>
							</listitem>
						</xsl:for-each>
					</itemizedlist>
				</para>
			</xsl:if>

			<xsl:apply-templates select="sectiondef"/>

			<xsl:for-each select="innerclass">
				<xsl:apply-templates select="ancestor::*/compounddef[@id = current()/@refid]"/>
			</xsl:for-each>

			<xsl:for-each select="innergroup">
				<xsl:apply-templates select="ancestor::*/compounddef[@kind = 'group' and @id = current()/@refid]"/>
			</xsl:for-each>
		</section>
	</xsl:template>

	<xsl:template match="compounddef[@kind = 'struct' or @kind = 'union']">
		<xsl:variable name="name" select="compoundname"/>

		<section id="{@id}" xreflabel="{$name}">
			<title>
				<xsl:choose>
					<xsl:when test="@kind = 'struct'">
						<xsl:text>Struct </xsl:text>
					</xsl:when>

					<xsl:when test="@kind = 'union'">
						<xsl:text>Union </xsl:text>
					</xsl:when>
				</xsl:choose>

				<xsl:value-of select="$name"/>
			</title>

			<xsl:call-template name="generate.index.id">
				<xsl:with-param name="name" select="$name"/>
			</xsl:call-template>

			<xsl:apply-templates select="detaileddescription"/>

			<xsl:for-each select="sectiondef[@kind = 'public-attrib']">
				<table>
					<title>
						<xsl:value-of select="$name"/>
					</title>

					<tgroup cols="3">
						<thead>
							<row>
								<entry>Type</entry>
								<entry>Name</entry>
								<entry>Description</entry>
							</row>
						</thead>

						<tbody>
							<xsl:for-each select="memberdef">
								<row id="{@id}" xreflabel="{name}">
									<entry>
										<xsl:value-of select="type"/>
									</entry>
									<entry>
										<xsl:value-of select="name"/>
										<xsl:if test="starts-with(argsstring, '[')">
											<xsl:text>[]</xsl:text>
										</xsl:if>

										<xsl:variable name="struct.element.name">
											<xsl:value-of select="$name"/>
											<xsl:text>.</xsl:text>
											<xsl:value-of select="name"/>
										</xsl:variable>

										<xsl:call-template name="generate.index.id">
											<xsl:with-param name="name" select="$struct.element.name"/>
										</xsl:call-template>
									</entry>
									<entry>
										<xsl:apply-templates select="detaileddescription"/>
									</entry>
								</row>
							</xsl:for-each>
						</tbody>
					</tgroup>
				</table>
			</xsl:for-each>
		</section>
	</xsl:template>

	<xsl:template match="memberdef[@kind = 'function']">
		<section id="{@id}" xreflabel="{name}">
			<title>
				<xsl:text>Function </xsl:text>
				<xsl:value-of select="name"/>
				<xsl:text>()</xsl:text>
			</title>

			<xsl:call-template name="generate.index.id">
				<xsl:with-param name="name" select="name"/>
			</xsl:call-template>

			<para>
				<emphasis role="italic">
					<xsl:value-of select="briefdescription"/>
				</emphasis>
			</para>

			<programlisting language="c">
				<emphasis role="keyword">
					<xsl:value-of select="type"/>
				</emphasis>
				<xsl:text> </xsl:text>
				<xsl:value-of select="name"/>
				<xsl:text>(</xsl:text>

				<xsl:choose>
					<xsl:when test="not(param[1]/declname)">
						<emphasis role="keyword">void</emphasis>
					</xsl:when>

					<xsl:otherwise>
						<xsl:for-each select="param">
							<xsl:if test="position() > 1">
								<xsl:text>,</xsl:text>
							</xsl:if>
							<xsl:text>&#10;&#9;</xsl:text>
							<emphasis role="keyword">
								<xsl:value-of select="type"/>
							</emphasis>
							<xsl:text> </xsl:text>
							<xsl:value-of select="declname"/>
						</xsl:for-each>
					</xsl:otherwise>
				</xsl:choose>

				<xsl:text>)</xsl:text>
			</programlisting>

			<xsl:apply-templates select="detaileddescription"/>
		</section>
	</xsl:template>

	<xsl:template match="memberdef[@kind = 'enum']">
		<section id="{@id}" xreflabel="{name}">
			<title>
				<xsl:text>Enum </xsl:text>
				<xsl:value-of select="name"/>
			</title>

			<xsl:call-template name="generate.index.id">
				<xsl:with-param name="name" select="name"/>
			</xsl:call-template>

			<xsl:apply-templates select="detaileddescription"/>

			<table>
				<title>Members</title>
				<tgroup cols="2">
					<thead>
						<row>
							<entry>Enum Value</entry>
							<entry>Description</entry>
						</row>
					</thead>

					<tbody>
						<xsl:for-each select="enumvalue">
							<row>
								<entry>
									<para id="{@id}" xreflabel="{name}">
										<xsl:value-of select="name"/>

										<xsl:call-template name="generate.index.id">
											<xsl:with-param name="name" select="name"/>
										</xsl:call-template>
									</para>
								</entry>
								<entry>
									<xsl:apply-templates select="detaileddescription"/>
								</entry>
							</row>
						</xsl:for-each>
					</tbody>
				</tgroup>
			</table>
		</section>
	</xsl:template>

	<xsl:template match="memberdef[@kind = 'define']">
		<section id="{@id}" xreflabel="{name}">
			<title>
				<xsl:text>Macro </xsl:text>
				<xsl:value-of select="name"/>
			</title>

			<xsl:call-template name="generate.index.id">
				<xsl:with-param name="name" select="name"/>
			</xsl:call-template>

			<programlisting language="c">
				<emphasis role="preprocessor">
					<xsl:text>#define </xsl:text>
					<xsl:value-of select="name"/>
					<xsl:if test="count(param) > 0">
						<xsl:text>(</xsl:text>
						<xsl:for-each select="param/defname">
							<xsl:if test="position() > 1">
								<xsl:text>,</xsl:text>
							</xsl:if>
							<xsl:value-of select="."/>
						</xsl:for-each>
						<xsl:text>)</xsl:text>
					</xsl:if>
					<xsl:text> </xsl:text>

					<!-- Split long macro definitions across multiple lines -->
					<xsl:if test="(string-length(initializer) > 50) or (count(param) > 0)">
						<xsl:text>\&#10;&#9;</xsl:text>
					</xsl:if>

					<xsl:value-of select="initializer"/>
				</emphasis>
				<xsl:text> </xsl:text>
			</programlisting>

			<xsl:apply-templates select="detaileddescription"/>
		</section>
	</xsl:template>

	<xsl:template match="memberdef[@kind = 'typedef']">
		<section id="{@id}" xreflabel="{name}">
			<title>
				<xsl:text>Type </xsl:text>
				<xsl:value-of select="name"/>
			</title>

			<xsl:call-template name="generate.index.id">
				<xsl:with-param name="name" select="name"/>
			</xsl:call-template>

			<programlisting language="c">
				<emphasis role="keyword">
					<xsl:text>typedef </xsl:text>
					<xsl:value-of select="type"/>
				</emphasis>
				<xsl:text> </xsl:text>
				<xsl:value-of select="name"/>
				<xsl:text> </xsl:text>
				<xsl:value-of select="argsstring"/>
			</programlisting>

			<xsl:apply-templates select="detaileddescription"/>
		</section>
	</xsl:template>


	<xsl:template match="memberdef[@kind = 'variable']">
		<section id="{@id}" xreflabel="{name}">
			<title>
				<xsl:text>Variable </xsl:text>
				<xsl:value-of select="name"/>
			</title>

			<xsl:call-template name="generate.index.id">
				<xsl:with-param name="name" select="name"/>
			</xsl:call-template>

			<programlisting language="c">
				<emphasis role="keyword">
					<xsl:value-of select="type"/>
				</emphasis>
				<xsl:text> </xsl:text>
				<xsl:value-of select="name"/>
			</programlisting>

			<xsl:apply-templates select="detaileddescription"/>
		</section>
	</xsl:template>

	<xsl:template match="linebreak | simplesectsep">
		<!-- MUST be on two separate lines, as this is a *literal* newline -->
		<literallayout>
		</literallayout>
	</xsl:template>

	<xsl:template match="verbatim">
		<programlisting>
			<xsl:apply-templates/>
		</programlisting>
	</xsl:template>

	<xsl:template match="sectiondef">
		<para>
			<xsl:value-of select="description"/>
		</para>

		<xsl:apply-templates select="memberdef"/>
	</xsl:template>

	<xsl:template match="simplesect" mode="struct">
		<footnote>
			<xsl:apply-templates/>
		</footnote>
	</xsl:template>

	<xsl:template match="simplesect">
		<xsl:choose>
			<xsl:when test="@kind = 'par'">
				<note>
					<title>
						<xsl:value-of select="title"/>
					</title>
					<xsl:apply-templates/>
				</note>
			</xsl:when>

			<xsl:when test="@kind = 'return'">
				<note>
					<title>Returns</title>
					<xsl:apply-templates/>
				</note>
			</xsl:when>

			<xsl:when test="@kind = 'warning'">
				<warning>
					<title>Warning</title>
					<xsl:apply-templates/>
				</warning>
			</xsl:when>

			<xsl:when test="@kind = 'pre'">
				<note>
					<title>Precondition</title>
					<xsl:apply-templates/>
				</note>
			</xsl:when>

			<xsl:when test="@kind = 'see'">
				<note>
					<title>See also</title>
					<xsl:apply-templates/>
				</note>
			</xsl:when>

			<xsl:when test="@kind = 'note'">
				<note>
					<title>Note</title>
					<xsl:apply-templates/>
				</note>
			</xsl:when>

		</xsl:choose>
	</xsl:template>

	<xsl:template match="parameterlist[@kind = 'param']">
		<table>
			<title>Parameters</title>
			<tgroup cols="3">
				<thead>
					<row>
						<entry>Data Direction</entry>
						<entry>Parameter Name</entry>
						<entry>Description</entry>
					</row>
				</thead>
				<tbody>
					<xsl:for-each select="parameteritem">
						<row>
							<xsl:apply-templates select="."/>
						</row>
					</xsl:for-each>
				</tbody>
			</tgroup>
		</table>
	</xsl:template>

	<xsl:template match="parameterlist[@kind = 'retval']">
		<table>
			<title>Return Values</title>
			<tgroup cols="2">
				<thead>
					<row>
						<entry>Return Value</entry>
						<entry>Description</entry>
					</row>
				</thead>
				<tbody>
					<xsl:for-each select="parameteritem">
						<row>
							<xsl:apply-templates select="."/>
						</row>
					</xsl:for-each>
				</tbody>
			</tgroup>
		</table>
	</xsl:template>

	<xsl:template match="parameteritem">
		<xsl:if test="parent::parameterlist/@kind = 'param'">
			<entry>
				<para>
					<xsl:choose>
						<xsl:when test="not(descendant::parametername/@direction)">
							<emphasis role="italic">?</emphasis>
						</xsl:when>

						<xsl:otherwise>
							<emphasis role="bold">
								[<xsl:value-of select="descendant::parametername/@direction"/>]
							</emphasis>
						</xsl:otherwise>
					</xsl:choose>
				</para>
			</entry>
		</xsl:if>

		<entry>
			<para>
				<xsl:value-of select="parameternamelist/parametername"/>
			</para>
		</entry>

		<entry>
			<xsl:apply-templates select="parameterdescription"/>
		</entry>
	</xsl:template>

	<xsl:template match="parameterdescription">
		<para>
			<xsl:apply-templates/>
		</para>
	</xsl:template>

	<xsl:template match="type">
		<xsl:apply-templates/>
	</xsl:template>

	<xsl:template match="bold">
		<emphasis role="bold">
			<xsl:apply-templates/>
		</emphasis>
	</xsl:template>

	<xsl:template match="emphasis">
		<emphasis role="italic">
			<xsl:apply-templates/>
		</emphasis>
	</xsl:template>

	<xsl:template match="small">
		<xsl:apply-templates/>
	</xsl:template>

	<xsl:template match="mdash | ndash">
		<!-- Doxygen bug; double dashed are replaced with single HTML dash
		     entities, even in verbatim-like <tt> sections -->
		<xsl:text>--</xsl:text>
	</xsl:template>

	<xsl:template match="computeroutput | preformatted">
		<computeroutput>
			<xsl:apply-templates/>
		</computeroutput>
	</xsl:template>

	<xsl:template match="codeline">
			<xsl:apply-templates/>
	</xsl:template>

	<xsl:template match="ulink">
		<ulink url="{@url}">
			<xsl:value-of select="."/>
		</ulink>
	</xsl:template>

	<xsl:template match="superscript">
		<superscript>
			<xsl:apply-templates/>
		</superscript>
	</xsl:template>

	<xsl:template match="subscript">
		<subscript>
			<xsl:apply-templates/>
		</subscript>
	</xsl:template>

	<xsl:template match="para">
		<para>
			<xsl:apply-templates/>
		</para>
	</xsl:template>

	<xsl:template match="ref">
		<xsl:choose>
			<!-- Don't show links inside program listings -->
			<xsl:when test="ancestor::programlisting">
				<xsl:value-of select="."/>
			</xsl:when>

			<!-- Don't show links to file compound definitions, as they are discarded -->
			<xsl:when test="ancestor::*/compounddef[@kind = 'file' and @id = current()/@refid]">
				<xsl:value-of select="."/>
			</xsl:when>

			<!-- Show links outside program listings -->
			<xsl:otherwise>
				<link linkend="{@refid}">
					<xsl:value-of select="text()"/>
				</link>
			</xsl:otherwise>
		</xsl:choose>
	</xsl:template>

	<xsl:template match="entry">
		<entry>
			<xsl:apply-templates/>
		</entry>
	</xsl:template>

	<xsl:template match="table[caption]">
		<table>
			<title>
				<xsl:value-of select="caption"/>
			</title>

			<tgroup cols="{@cols}">
				<thead>
					<xsl:apply-templates select="row[entry/@thead = 'yes']"/>
				</thead>

				<tbody>
					<xsl:apply-templates select="row[entry/@thead != 'yes']"/>
				</tbody>
			</tgroup>
		</table>
	</xsl:template>

	<xsl:template match="table[not(caption)]">
		<informaltable>
			<tgroup cols="{@cols}">
				<thead>
					<xsl:apply-templates select="row[entry/@thead = 'yes']"/>
				</thead>

				<tbody>
					<xsl:apply-templates select="row[entry/@thead != 'yes']"/>
				</tbody>
			</tgroup>
		</informaltable>
	</xsl:template>

	<xsl:template match="row">
		<row>
			<xsl:apply-templates/>
		</row>
	</xsl:template>

	<xsl:template match="itemizedlist">
		<itemizedlist>
			<xsl:apply-templates/>
		</itemizedlist>
	</xsl:template>

	<xsl:template match="orderedlist">
		<orderedlist>
			<xsl:apply-templates/>
		</orderedlist>
	</xsl:template>

	<xsl:template match="listitem">
		<listitem>
			<xsl:apply-templates/>
		</listitem>
	</xsl:template>

	<xsl:template match="programlisting">
		<programlisting language="c">
			<xsl:for-each select="codeline[position() > 1 or highlight]">
				<xsl:apply-templates select="."/>
				<xsl:text>&#10;</xsl:text>
			</xsl:for-each>
		</programlisting>
	</xsl:template>

	<xsl:template match="highlight">
		<emphasis role="{@class}">
			<xsl:apply-templates/>
		</emphasis>
	</xsl:template>

	<xsl:template match="highlight[1]/text()">
		<xsl:choose>
			<xsl:when test="substring(., 1, 1) = '*'">
				<xsl:value-of select="substring(., 2)"/>
			</xsl:when>

			<xsl:otherwise>
				<xsl:value-of select="."/>
			</xsl:otherwise>
		</xsl:choose>
	</xsl:template>

	<xsl:template match="sp[ancestor::codeline]">
		<xsl:text> </xsl:text>
	</xsl:template>

	<xsl:template match="image">
		<mediaobject>
			<imageobject>
				<imagedata align="center">
					<xsl:attribute name="fileref">
						<xsl:text>images/</xsl:text>
						<xsl:value-of select="@name"/>
					</xsl:attribute>
				</imagedata>
			</imageobject>
		</mediaobject>
	</xsl:template>

	<xsl:template match="detaileddescription">
		<xsl:apply-templates/>
	</xsl:template>

	<xsl:template match="sect1 | sect2 | sect3 | sect4 | sect5 | sect6 | sect7 | sect8 | sect9">
		<section>
			<xsl:if test="@id">
				<xsl:attribute name="id">
					<xsl:value-of select="@id"/>
				</xsl:attribute>
			</xsl:if>

			<title>
				<xsl:value-of select="title"/>
			</title>

			<xsl:apply-templates/>
		</section>
	</xsl:template>

	<xsl:template match="anchor">
		<xsl:if test="@id">
			<indexterm id="{@id}"/>
		</xsl:if>
	</xsl:template>

	<xsl:template match="title"/>

	<xsl:template match="htmlonly"/>

	<xsl:template match="*">
		<xsl:message>NO XSL TEMPLATE MATCH: <xsl:value-of select="local-name()"/></xsl:message>
	</xsl:template>

</xsl:stylesheet>

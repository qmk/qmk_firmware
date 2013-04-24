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
			<xsl:call-template name="generate.top.level.page">
				<xsl:with-param name="top.level.page" select="compounddef[@kind = 'page' and contains(@id, 'index')]"/>
			</xsl:call-template>

			<!-- Add free-floating chapters -->
			<xsl:for-each select="compounddef[@kind = 'page' and not(contains(@id, 'index'))]">
				<xsl:if test="not(//innerpage[@refid = current()/@id])">
					<xsl:call-template name="generate.top.level.page">
						<xsl:with-param name="top.level.page" select="current()"/>
					</xsl:call-template>
				</xsl:if>
			</xsl:for-each>

			<!-- Add Module chapter -->
			<chapter>
				<title>Modules</title>
				<xsl:for-each select="compounddef[@kind = 'group']">
					<xsl:if test="not(//innergroup[@refid = current()/@id])">
						<xsl:apply-templates select="current()"/>
					</xsl:if>
				</xsl:for-each>
			</chapter>
		</book>
	</xsl:template>

	<xsl:template name="generate.top.level.page">
		<xsl:param name="top.level.page"/>

		<chapter id="{$top.level.page/@id}">
			<title>
				<xsl:value-of select="$top.level.page/title"/>
			</title>

			<xsl:apply-templates select="$top.level.page/detaileddescription"/>

			<xsl:for-each select="$top.level.page/innerpage">
				<xsl:apply-templates select="ancestor::*/compounddef[@kind = 'page' and @id = current()/@refid]"/>
			</xsl:for-each>
		</chapter>
	</xsl:template>

	<xsl:template match="compounddef">
		<!-- Discard compounddef elements unless a later template matches -->
	</xsl:template>

	<xsl:template match="compounddef[@kind = 'page']">
		<section id="{@id}">
			<title>
				<xsl:value-of select="title"/>
			</title>

			<xsl:apply-templates select="detaileddescription"/>

			<xsl:for-each select="innerpage">
				<xsl:apply-templates select="ancestor::*/compounddef[@kind = 'page' and @id = current()/@refid]"/>
			</xsl:for-each>
		</section>
	</xsl:template>

	<xsl:template match="compounddef[@kind = 'group']">
		<section id="{@id}">
			<title>
				<xsl:value-of select="title"/>
			</title>

			<xsl:variable name="book.title">
				<xsl:call-template name="generate.book.title"/>
			</xsl:variable>

			<xsl:variable name="name">
				<xsl:choose>
					<xsl:when test="contains(compoundname, '_')">
						<xsl:value-of select="translate(compoundname, '_', '/')"/>
						<xsl:text>.h</xsl:text>
					</xsl:when>
					<xsl:otherwise>
						<xsl:value-of select="compoundname"/>
						<xsl:text>.h</xsl:text>
					</xsl:otherwise>
				</xsl:choose>
			</xsl:variable>

			<xsl:variable name="name.escaped">
				<xsl:choose>
					<xsl:when test="contains(compoundname, '_')">
						<xsl:value-of select="translate(compoundname, '_', '.')"/>
						<xsl:text>.h</xsl:text>
					</xsl:when>
					<xsl:otherwise>
						<xsl:value-of select="compoundname"/>
						<xsl:text>.h</xsl:text>
					</xsl:otherwise>
				</xsl:choose>
			</xsl:variable>

			<indexterm id="{$keyword.namespace}.{$name.escaped}">
				<primary>Header</primary>
				<secondary>
					<xsl:value-of select="$name"/>
				</secondary>
			</indexterm>

			<xsl:call-template name="generate.index.id">
				<xsl:with-param name="name" select="$name"/>
			</xsl:call-template>

			<indexterm>
				<primary>
					<xsl:value-of select="$name"/>
				</primary>
			</indexterm>

			<xsl:apply-templates select="detaileddescription" />

			<xsl:apply-templates select="sectiondef" />

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

			<xsl:for-each select="sectiondef[@kind='public-attrib']">
				<table tabstyle="striped">
					<title>
						<xsl:value-of select="$name"/>
					</title>
					<tgroup cols="3">
						<colspec colnum="1" colname="start.col"/>
						<colspec colnum="3" colname="stop.col"/>
						<spanspec spanname="full" namest="start.col" nameend="stop.col"/>
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
										<xsl:apply-templates select="type"/>
									</entry>
									<entry>
										<xsl:value-of select="name"/>
										<xsl:if test="starts-with(argsstring, '[')">
											<xsl:text>[]</xsl:text>
										</xsl:if>
										<indexterm id="{$keyword.namespace}.{$name}.{name}"/>
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
		<xsl:variable name="name" select="name"/>

		<section id="{@id}" xreflabel="{name}">
			<title>
				<xsl:text>Function </xsl:text>
				<xsl:value-of select="$name"/>
				<xsl:text>()</xsl:text>
			</title>

			<xsl:call-template name="generate.index.id">
				<xsl:with-param name="name" select="$name"/>
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
					<xsl:when test="argsstring = '(void)'">
						<emphasis role="keyword">void</emphasis>
					</xsl:when>

					<xsl:otherwise>
						<xsl:for-each select="param">
							<xsl:if test="position() > 1">
								<xsl:text>,</xsl:text>
							</xsl:if>
							<xsl:text>&#10;&#9;&#9;</xsl:text>
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
		<xsl:variable name="name" select="name"/>

		<section id="{@id}" xreflabel="{name}">
			<title>
				<xsl:text>Enum </xsl:text>
				<xsl:value-of select="$name"/>
			</title>

			<xsl:call-template name="generate.index.id">
				<xsl:with-param name="name" select="$name"/>
			</xsl:call-template>

			<xsl:apply-templates select="detaileddescription"/>

			<table tabstyle="striped">
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
										<indexterm id="{$keyword.namespace}.{$name}.{name}"/>
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
		<xsl:variable name="name" select="name"/>

		<section id="{@id}" xreflabel="{name}">
			<title>
				<xsl:text>Macro </xsl:text>
				<xsl:value-of select="name"/>
			</title>

			<xsl:call-template name="generate.index.id">
				<xsl:with-param name="name" select="$name"/>
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
						<xsl:text>\&#10;&#09;&#9;</xsl:text>
					</xsl:if>

					<xsl:value-of select="initializer"/>
				</emphasis>
				<xsl:text> </xsl:text>
			</programlisting>

			<xsl:apply-templates select="detaileddescription"/>
		</section>
	</xsl:template>

	<xsl:template match="memberdef[@kind = 'variable' or @kind = 'typedef']">
		<xsl:variable name="name" select="name"/>

		<section id="{@id}" xreflabel="{name}">
			<!-- Doxygen gets confused and thinks function pointer type definitions
				 are variables, so we need to map them to this common section and
				 check the definition to see which of the two it is. -->
			<xsl:choose>
				<xsl:when test="contains(definition,'typedef')">
					<title>
						<xsl:text>Type </xsl:text>
						<xsl:value-of select="name"/>
					</title>

					<xsl:call-template name="generate.index.id">
						<xsl:with-param name="name" select="$name"/>
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
				</xsl:when>

				<xsl:otherwise>
					<title>
						<xsl:text>Variable </xsl:text>
						<xsl:value-of select="name"/>
					</title>

					<xsl:call-template name="generate.index.id">
						<xsl:with-param name="name" select="$name"/>
					</xsl:call-template>

					<programlisting language="c">
						<emphasis role="keyword">
							<xsl:value-of select="type"/>
						</emphasis>
						<xsl:text> </xsl:text>
						<xsl:value-of select="name"/>
					</programlisting>
				</xsl:otherwise>
			</xsl:choose>

			<xsl:apply-templates select="detaileddescription"/>
		</section>
	</xsl:template>

	<xsl:template match="linebreak">
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
			<xsl:when test="@kind = 'warning'">
				<warning>
					<title>Warning</title>
					<xsl:apply-templates select="para"/>
				</warning>
			</xsl:when>

			<xsl:when test="@kind = 'return'">
				<note>
					<title>Returns</title>
					<xsl:apply-templates select="para"/>
				</note>
			</xsl:when>

			<xsl:when test="@kind = 'pre'">
				<note>
					<title>Precondition</title>
					<xsl:apply-templates select="para"/>
				</note>
			</xsl:when>

			<xsl:when test="@kind = 'par'">
				<note>
					<title>
						<xsl:value-of select="title"/>
					</title>
					<xsl:apply-templates select="para"/>
				</note>
			</xsl:when>

			<xsl:when test="@kind = 'see'">
				<note>
					<title>See also</title>
					<xsl:apply-templates select="para"/>
				</note>
			</xsl:when>

			<xsl:when test="@kind = 'note'">
				<note>
					<title>Note</title>
					<xsl:apply-templates select="para"/>
				</note>
			</xsl:when>

		</xsl:choose>
	</xsl:template>

	<xsl:template match="parameterlist[@kind = 'param']">
		<table tabstyle="striped">
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
		<table tabstyle="striped">
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

	<xsl:template match="type">
		<xsl:apply-templates/>
	</xsl:template>

	<xsl:template match="para">
		<para>
			<xsl:apply-templates/>
		</para>
	</xsl:template>

	<xsl:template match="bold">
		<emphasis role="bold">
			<xsl:value-of select="."/>
		</emphasis>
	</xsl:template>

	<xsl:template match="emphasis">
		<emphasis role="italic">
			<xsl:value-of select="."/>
		</emphasis>
	</xsl:template>

	<xsl:template match="computeroutput">
		<computeroutput>
			<xsl:value-of select="."/>
		</computeroutput>
	</xsl:template>

	<xsl:template match="ulink">
		<ulink url="{@url}">
			<xsl:value-of select="."/>
		</ulink>
	</xsl:template>

	<xsl:template match="registered">
		<xsl:text>&#174;</xsl:text>
	</xsl:template>

	<xsl:template match="copy">
		<xsl:text>&#169;</xsl:text>
	</xsl:template>

	<xsl:template match="trademark">
		<xsl:text>&#8482;</xsl:text>
	</xsl:template>

	<xsl:template match="superscript">
		<superscript>
			<xsl:value-of select="."/>
		</superscript>
	</xsl:template>

	<xsl:template match="subscript">
		<subscript>
			<xsl:value-of select="."/>
		</subscript>
	</xsl:template>

	<xsl:template match="ref">
		<xsl:choose>
			<!-- Don't show links inside program listings -->
			<xsl:when test="ancestor::programlisting">
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

	<xsl:template match="table">
		<xsl:choose>
			<xsl:when test="caption">
				<table tabstyle="striped">
					<title>
						<xsl:value-of select="caption"/>
					</title>
					<xsl:call-template name="write.table.content"/>
				</table>
			</xsl:when>
			<xsl:otherwise>
				<informaltable tabstyle="striped">
					<xsl:call-template name="write.table.content"/>
				</informaltable>
			</xsl:otherwise>
		</xsl:choose>
	</xsl:template>

	<xsl:template name="write.table.content">
		<tgroup cols="{@cols}">
			<thead>
				<xsl:for-each select="row[1]">
					<row>
						<xsl:for-each select="entry">
							<entry>
								<xsl:apply-templates select="."/>
							</entry>
						</xsl:for-each>
					</row>
				</xsl:for-each>
			</thead>
			<tbody>
				<xsl:for-each select="row[position() != 1]">
					<row>
						<xsl:for-each select="entry">
							<entry>
								<xsl:apply-templates select="."/>
							</entry>
						</xsl:for-each>
					</row>
				</xsl:for-each>
			</tbody>
		</tgroup>
	</xsl:template>

	<xsl:template match="itemizedlist">
		<itemizedlist>
			<xsl:apply-templates select="listitem"/>
		</itemizedlist>
	</xsl:template>

	<xsl:template match="orderedlist">
		<orderedlist>
			<xsl:apply-templates select="listitem"/>
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

	<xsl:template match="sp[ancestor::codeline]">
		<xsl:text> </xsl:text>
	</xsl:template>

	<xsl:template match="image">
		<mediaobject>
			<imageobject>
				<imagedata>
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

</xsl:stylesheet>

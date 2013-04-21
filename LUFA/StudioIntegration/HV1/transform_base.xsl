<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet
  xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
  xmlns:exsl="http://exslt.org/common"
  extension-element-prefixes="exsl"
  exclude-result-prefixes="exsl"
  version="1.0">

  <xsl:output
    method="xml" indent="yes"
    doctype-public="-//OASIS//DTD DocBook XML V4.5//EN"
    doctype-system="http://www.oasis-open.org/docbook/xml/4.5/docbookx.dtd"/>

  <xsl:template name="write.api.overview.contents">

      <xsl:if test="count(ancestor::*/sectiondef[memberdef/@kind = 'variable' or memberdef/@kind = 'typedef']) > 0">
        <section>
          <title>Variable and Type Definitions</title>

          <xsl:for-each select="ancestor::*/sectiondef[memberdef/@kind = 'variable' or memberdef/@kind = 'typedef']">
            <section>
              <title>
                <xsl:value-of select="header"/>
              </title>

              <xsl:apply-templates select="description"/>
              <xsl:apply-templates select="memberdef[@kind = 'variable' or @kind = 'typedef']"/>
            </section>
          </xsl:for-each>
        </section>
      </xsl:if>

      <xsl:if test="count(ancestor::*/innerclass) > 0">
        <section>
          <title>Structure Definitions</title>

          <xsl:for-each select="ancestor::*/innerclass">
            <xsl:apply-templates select="ancestor::*/compounddef[@id = current()/@refid]"/>
          </xsl:for-each>
        </section>
      </xsl:if>

      <xsl:if test="count(ancestor::*/sectiondef[memberdef/@kind = 'define' or @kind = 'define']) > 0">
        <section>
          <title>Macro Definitions</title>

          <xsl:for-each select="ancestor::*/sectiondef[memberdef/@kind = 'define' or @kind = 'define']">
            <section>
              <title>
                <xsl:value-of select="header"/>
              </title>

              <xsl:apply-templates select="description"/>
              <xsl:apply-templates select="memberdef[@kind = 'define']"/>
            </section>
          </xsl:for-each>
        </section>
      </xsl:if>

      <xsl:if test="count(ancestor::*/sectiondef[memberdef/@kind = 'function']) > 0">
        <section>
          <title>Function Definitions</title>

          <xsl:for-each select="ancestor::*/sectiondef[memberdef/@kind = 'function']">
            <section>
              <title>
                <xsl:value-of select="header"/>
              </title>

              <xsl:apply-templates select="description"/>
              <xsl:apply-templates select="memberdef[@kind = 'function']"/>
            </section>
          </xsl:for-each>
        </section>
      </xsl:if>

      <xsl:if test="count(ancestor::*/sectiondef[@kind = 'enum']) > 0">
        <section>
          <title>Enumeration Definitions</title>

          <xsl:apply-templates select="ancestor::*/sectiondef[@kind = 'enum']"/>
        </section>
      </xsl:if>

  </xsl:template>

  <xsl:template match="compounddef">
    <!-- Discard compounddef elements unless a later template matches -->
  </xsl:template>

  <xsl:template match="compounddef[@kind = 'struct' or @kind = 'union']">
    <section id="{@id}" xreflabel="{compoundname}">
      <title>
        <xsl:choose>
          <xsl:when test="@kind = 'struct'">
            <xsl:text>Struct </xsl:text>
          </xsl:when>
          <xsl:when test="@kind = 'union'">
            <xsl:text>Union </xsl:text>
          </xsl:when>
        </xsl:choose>

        <xsl:value-of select="compoundname"/>
      </title>

      <xsl:apply-templates select="detaileddescription"/>

      <xsl:for-each select="sectiondef[@kind = 'public-attrib']">
        <informaltable tabstyle="striped">
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
                    <xsl:apply-templates select="type"/>
                  </entry>
                  <entry>
                    <xsl:value-of select="name"/>
                    <xsl:if test="starts-with(argsstring, '[')">
                      <xsl:text>[]</xsl:text>
                    </xsl:if>
                  </entry>
                  <entry>
                    <xsl:apply-templates select="detaileddescription" mode="struct"/>
                  </entry>
                </row>
              </xsl:for-each>
            </tbody>
          </tgroup>
        </informaltable>
        <para>&#xa0;</para>
      </xsl:for-each>
    </section>
  </xsl:template>

  <xsl:template match="memberdef[@kind = 'function']">
    <section id="{@id}" xreflabel="{name}">
      <title> Function <xsl:value-of select="name"/>() </title>

      <para>
        <emphasis role="italic">
          <xsl:value-of select="briefdescription"/>
        </emphasis>
      </para>

      <programlisting language="c">
        <xsl:value-of select="definition"/>
        <xsl:text>&#10;&#9;&#9;</xsl:text>
        <xsl:apply-templates select="argsstring"/>
      </programlisting>

      <xsl:apply-templates select="detaileddescription"/>

      <para>&#xa0;</para>
    </section>
  </xsl:template>

  <xsl:template match="memberdef[@kind = 'enum']">
    <section id="{@id}" xreflabel="{name}">
      <title> Enum <xsl:value-of select="name"/> </title>

      <xsl:apply-templates select="detaileddescription"/>

      <informaltable tabstyle="striped">
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
                  </para>
                </entry>
                <entry>
                  <xsl:apply-templates select="detaileddescription"/>
                </entry>
              </row>
            </xsl:for-each>
          </tbody>
        </tgroup>
      </informaltable>

      <para>&#xa0;</para>
    </section>
  </xsl:template>

  <xsl:template match="memberdef[@kind = 'define']">
    <section id="{@id}" xreflabel="{name}">
      <title> Macro <xsl:value-of select="name"/> </title>

      <programlisting language="c">
        <xsl:text>#define </xsl:text>
        <xsl:value-of select="name"/>
        <xsl:if test="count(param) > 0">
          <xsl:text>(</xsl:text>
          <xsl:for-each select="param/defname">
            <xsl:if test="position() > 1">
              <xsl:text>, </xsl:text>
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
      </programlisting>

      <xsl:apply-templates select="detaileddescription"/>

      <para>&#xa0;</para>
    </section>
  </xsl:template>

  <xsl:template match="memberdef[@kind = 'variable' or @kind = 'typedef']">
    <section id="{@id}" xreflabel="{name}">
      <title>
        <!-- Doxygen gets confused and thinks function pointer type definitions
             are variables, so we need to map them to this common section and
             check the definition to see which of the two it is. -->
        <xsl:choose>
          <xsl:when test="contains(definition,'typedef')">
            <xsl:text>Type </xsl:text>
          </xsl:when>

          <xsl:otherwise>
            <xsl:text>Variable </xsl:text>
          </xsl:otherwise>
        </xsl:choose>

        <xsl:value-of select="name"/>
      </title>

      <programlisting language="c">
        <xsl:value-of select="definition"/>
      </programlisting>

      <xsl:apply-templates select="detaileddescription"/>

      <para>&#xa0;</para>
    </section>
  </xsl:template>

  <xsl:template match="sectiondef">
    <para>
      <xsl:value-of select="description"/>
    </para>

    <xsl:apply-templates select="memberdef"/>
  </xsl:template>

  <xsl:template match="simplesect" mode="struct">
    <footnote>
      <xsl:apply-templates select="para"/>
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
        <!-- Notes can have special prefix keywords to transform them into
             special styles for training documents ("AlfonsoNotes(TM)") -->
        <xsl:variable name="note.prefix" select="substring-before(para[1]/text(), ' ')"/>

        <note>
          <xsl:choose>
            <xsl:when test="$note.prefix = 'TODO:'">
              <xsl:attribute name="role">todo</xsl:attribute>
              <title>To Do</title>
            </xsl:when>

            <xsl:when test="$note.prefix = 'TIP:'">
              <xsl:attribute name="role">tip</xsl:attribute>
              <title>Tip</title>
            </xsl:when>

            <xsl:when test="$note.prefix = 'INFO:'">
              <xsl:attribute name="role">info</xsl:attribute>
              <title>Info</title>
            </xsl:when>

            <xsl:when test="$note.prefix = 'RESULT:'">
              <xsl:attribute name="role">result</xsl:attribute>
              <title>Result</title>
            </xsl:when>

            <xsl:when test="$note.prefix = 'EXECUTE:'">
              <xsl:attribute name="role">execute</xsl:attribute>
              <title>Execute</title>
            </xsl:when>

            <xsl:when test="$note.prefix = 'WARNING:'">
              <xsl:attribute name="role">warning</xsl:attribute>
              <title>Warning</title>
            </xsl:when>

            <xsl:otherwise/>
          </xsl:choose>

          <xsl:apply-templates select="para"/>
        </note>
      </xsl:when>

    </xsl:choose>
  </xsl:template>

  <!-- Strip off the special note type prefix from the special training document
       style notes ("AlfonsoNotes(TM)") if one is present. -->
  <xsl:template match="para[parent::simplesect/@kind='note']/text()">
    <xsl:variable name="note.prefix" select="substring-before(., ' ')"/>
    <xsl:variable name="note.content" select="substring-after(., ' ')"/>

    <xsl:choose>
      <xsl:when test="$note.prefix = 'TODO:'">
        <xsl:value-of select="$note.content"/>
      </xsl:when>

      <xsl:when test="$note.prefix = 'TIP:'">
        <xsl:value-of select="$note.content"/>
      </xsl:when>

      <xsl:when test="$note.prefix = 'INFO:'">
        <xsl:value-of select="$note.content"/>
      </xsl:when>

      <xsl:when test="$note.prefix = 'RESULT:'">
        <xsl:value-of select="$note.content"/>
      </xsl:when>

      <xsl:when test="$note.prefix = 'EXECUTE:'">
        <xsl:value-of select="$note.content"/>
      </xsl:when>

      <xsl:when test="$note.prefix = 'WARNING:'">
        <xsl:value-of select="$note.content"/>
      </xsl:when>

      <xsl:otherwise>
        <xsl:value-of select="."/>
      </xsl:otherwise>
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
              <emphasis role="bold">[<xsl:value-of select="descendant::parametername/@direction"/>]</emphasis>
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

  <xsl:template match="sect1">
    <section id="{@id}" xreflabel="{title}">
      <title>
        <xsl:value-of select="title"/>
      </title>

      <xsl:apply-templates select="para"/>
      <xsl:apply-templates select="sect2"/>
    </section>
  </xsl:template>

  <xsl:template match="sect2">
    <section id="{@id}" xreflabel="{title}">
      <title>
        <xsl:value-of select="title"/>
      </title>

      <xsl:apply-templates select="para"/>
      <xsl:apply-templates select="sect3"/>
    </section>
  </xsl:template>

  <xsl:template match="sect3">
    <section id="{@id}" xreflabel="{title}">
      <title>
        <xsl:value-of select="title"/>
      </title>

      <xsl:apply-templates select="para"/>
    </section>
  </xsl:template>

  <xsl:template match="detaileddescription">
    <xsl:apply-templates select="para"/>
    <xsl:apply-templates select="sect1"/>
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

  <xsl:template match="ref">
    <xsl:choose>
      <!-- Don't show links inside program listings -->
      <xsl:when test="ancestor::programlisting">
        <xsl:value-of select="."/>
      </xsl:when>

      <!-- Show links outside program listings -->
      <xsl:otherwise>
        <link linkend="{@refid}" xrefstyle="nopage">
          <xsl:value-of select="text()"/>
        </link>
      </xsl:otherwise>
    </xsl:choose>
  </xsl:template>

  <xsl:template match="formula">
    <equation>
      <!-- LaTeX equation generation requires JLatexMath and its associated
           FOP plugin, or you will get missing equations in the output -->
      <latex align="center" xmlns="http://forge.scilab.org/p/jlatexmath">
        <xsl:value-of select="."/>
      </latex>
    </equation>
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
    <emphasis>
      <xsl:attribute name="role">
        <xsl:value-of select="@class"/>
      </xsl:attribute>
      <xsl:apply-templates/>
    </emphasis>
  </xsl:template>

  <xsl:template match="sp[ancestor::codeline]">
    <xsl:choose>
      <!-- Need to check if this is the first part of the line - if so we may
           need to strip off any leading <sp/> element indentation -->
      <xsl:when test="ancestor::highlight = ancestor::codeline/highlight[1]">
        <!-- Doxygen retains a level of indentation in some code fragments - obtain
             the base indentation level by counting the leading <sp/> elements of the
             first code line, and use that to remove the indentation on the rest -->
        <xsl:variable name="leading.spaces" select="count(ancestor::programlisting/codeline[highlight][1]/highlight[1]/sp[not(preceding-sibling::text())])"/>

        <xsl:if test="position() > $leading.spaces">
          <xsl:text> </xsl:text>
        </xsl:if>
      </xsl:when>

      <xsl:otherwise>
        <xsl:text> </xsl:text>
      </xsl:otherwise>
    </xsl:choose>
  </xsl:template>

  <xsl:template match="image">
    <figure>
      <title>
        <xsl:value-of select="."/>
      </title>

      <mediaobject>
        <imageobject>
          <imagedata scalefit="1" width="{@width}">
            <xsl:attribute name="fileref">html/<xsl:value-of select="@name"/></xsl:attribute>
          </imagedata>
        </imageobject>
      </mediaobject>
    </figure>
  </xsl:template>

  <xsl:template match="anchor">
    <anchor id="{@id}"/>
  </xsl:template>

  <xsl:template match="dot">
    <!-- We get raw DOT syntax rather than a rendered image: write the DOT code
         to a new unique file, and make a image reference to a SVG version of
         that file. The build system should then call dot to render all generated
         DOT files into their SVG equivalents before rendering the PDF. -->
    <xsl:variable name="filename" select="generate-id(.)" />
    <exsl:document href="{$filename}.dot" method="text">
      <xsl:value-of select="." />
    </exsl:document>

    <figure>
      <title>
        <xsl:value-of select="ancestor::*/title"/>
      </title>
      <mediaobject>
        <imageobject>
          <imagedata format="SVG">
            <xsl:attribute name="fileref">
                <xsl:value-of select="$filename" />
                <xsl:text>.svg</xsl:text>
            </xsl:attribute>
          </imagedata>
        </imageobject>
      </mediaobject>
    </figure>
  </xsl:template>

  <xsl:template match="argsstring" name="split.functions.args">
    <xsl:param name="text" select="."/>
    <xsl:value-of select="substring-before(concat($text,','),',')"/>
    <xsl:if test="contains($text,',')">
      <xsl:text>,&#10;&#09;&#9;</xsl:text>
      <xsl:call-template name="split.functions.args">
        <xsl:with-param name="text" select="substring-after($text,',')"/>
      </xsl:call-template>
    </xsl:if>
  </xsl:template>
</xsl:stylesheet>

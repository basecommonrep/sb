<?xml version="1.0" encoding="UTF-8" ?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

  <xsl:param name="language">en</xsl:param>

  <xsl:output method="html" version="4.0" media-type="text/html; charset=UTF-8" indent="yes"/>

  <!-- The file "labels.xsl" defines constants that are localized -->
  <xsl:include href="../.././images/madridall/labels.xsl"/>

  <!-- The file "inid.xsl" defines templates to retrieve and display the ID and the  -->
  <!-- Description of an INID, based on its name -->
  <xsl:include href="../.././images/madridall/inid.xsl"/>

  <xsl:strip-space elements="*" />

  <!--	Changes
	Roger Holberton   01/11/2004	Change country specific display to always include CBN* and PCN
  -->
  <!-- Main template for the HTML output -->
  <xsl:template match="/">
    <xsl:element name="html">
      <!-- Head of the HTML document -->
      <xsl:element name="head">
        <xsl:element name="title">
           <xsl:call-template name="getNavigationLabel">
               <xsl:with-param name="label">title</xsl:with-param>
           </xsl:call-template>
        </xsl:element>
        <xsl:element name="link">
          <xsl:attribute name="href">images/madridall/romarin.css</xsl:attribute>
          <xsl:attribute name="rel">stylesheet</xsl:attribute>
          <xsl:attribute name="type">text/css</xsl:attribute>
        </xsl:element>
        <xsl:element name="style">
          <xsl:attribute name="type">text/css</xsl:attribute>
          <![CDATA[
          ]]>
        </xsl:element>
      </xsl:element>

      <!-- Body of the HTML document -->
      <xsl:element name="body">
<!--        <xsl:attribute name="topmargin">0</xsl:attribute>
-->
        <xsl:element name="table">
          <xsl:attribute name="width">100%</xsl:attribute>
          <xsl:attribute name="cellpadding">0</xsl:attribute>
          <xsl:attribute name="cellspacing">0</xsl:attribute>
          <xsl:attribute name="border">0</xsl:attribute>
	<xsl:element name="tr">
	<xsl:element name="td">

          <!-- Display the first table: Mark information -->
          <xsl:element name="table">
            <xsl:attribute name="width">100%</xsl:attribute>
            <xsl:attribute name="cellpadding">2</xsl:attribute>
            <xsl:attribute name="cellspacing">1</xsl:attribute>
            <xsl:attribute name="border">0</xsl:attribute>
            <xsl:for-each select="MARKGR">
              <xsl:call-template name="MARKGR"/>
            </xsl:for-each>
          </xsl:element>

          <!-- For every "block" (child of the MARKGR node), but the "MAN", "MTN" and "TRN" ones, create a new <div> element -->
          <!-- containing a <table> element -->
          <xsl:for-each select="MARKGR/*[(name() != 'MAN') and (name() != 'MTN') and (name() != 'TRN')]">
            <xsl:element name="div">
              <xsl:attribute name="id">div_<xsl:value-of select="generate-id(.)"/></xsl:attribute>
              <xsl:element name="table">
                <xsl:attribute name="width">100%</xsl:attribute>
                <xsl:attribute name="cellpadding">2</xsl:attribute>
                <xsl:attribute name="cellspacing">1</xsl:attribute>
                <xsl:attribute name="border">0</xsl:attribute>
<!--                <xsl:attribute name="bgcolor">#f0f0f0</xsl:attribute> -->
                <xsl:element name="tr">
                  <xsl:element name="td">
                    <xsl:attribute name="bgcolor">white</xsl:attribute>
                    <xsl:attribute name="colspan">3</xsl:attribute>
                    <xsl:attribute name="class">labelGS</xsl:attribute>
                    &#160;
                  </xsl:element>
                </xsl:element>
                <xsl:call-template name="Block"/>
              </xsl:element>
            </xsl:element>
          </xsl:for-each>

        </xsl:element>
	</xsl:element>
	</xsl:element>

      </xsl:element>
      
      
      
      
    </xsl:element>
  </xsl:template>


  <!-- Template for the first table of the HTML page -->
  <xsl:template name="MARKGR">
    <xsl:element name="tr">
      <xsl:element name="td">
        <xsl:attribute name="colspan">3</xsl:attribute>
        <xsl:attribute name="class">markhead</xsl:attribute>
        <xsl:value-of select="./@INTREGN"/>
      </xsl:element>
    </xsl:element>
    <xsl:for-each select="./@*">
      <xsl:choose>
        <xsl:when test="(name() = 'INTREGN') or (name() = 'BILING') or (name() = 'OOCD')">
        </xsl:when>
        <xsl:when test="(name() = 'ORIGLAN')">
          <xsl:call-template name="formatLineSingle">
            <xsl:with-param name="value">
              <xsl:call-template name="getLanguageFromID">
                <xsl:with-param name="langID">
                  <xsl:value-of select="."/>
                </xsl:with-param>
              </xsl:call-template>
            </xsl:with-param>
          </xsl:call-template>
        </xsl:when>
        <xsl:otherwise>
          <xsl:call-template name="formatLineSingle">
            <xsl:with-param name="value" select="."/>
          </xsl:call-template>
        </xsl:otherwise>
      </xsl:choose>
    </xsl:for-each>
  </xsl:template>


  <!-- Template applied on every child of the MARKGR root node -->
  <xsl:template name="Block">
    <xsl:call-template name="formatLineLabel">
      <xsl:with-param name="class" select="'labelBlock'"/>
      <xsl:with-param name="classinid" select="'labelBlock'"/>
    </xsl:call-template>

    <!-- If present, display the INTOFF attribute in the very first place, without any label    -->
    <!-- Special case : do not display the INTOFF for the following blocks :                    -->
    <!--      ENN, EXN, LIN, NLCN, RNN, CPN, FBN, DBN, RAN, PCN, CBN1, CBNP and CBNT            -->
    <!-- Special case : for the HRN block, display the INTOFF with a label, and after the GAZNO -->
    <xsl:if test="not(contains(name(),'ENN')) and not(contains(name(),'EXN')) and
                  not(contains(name(),'LIN')) and not(contains(name(),'NLCN'))and
                  not(contains(name(),'RNN')) and not(contains(name(),'CPN')) and
                  not(contains(name(),'FBN')) and not(contains(name(),'DBN')) and
                  not(contains(name(),'RAN')) and not(contains(name(),'PCN')) and
                  not(contains(name(),'CBN1')) and not(contains(name(),'CBNP')) and
                  not(contains(name(),'CBNT')) and not(contains(name(),'HRN'))  and
                  not(contains(name(),'EEN'))">
      <xsl:for-each select="./@INTOFF">
        <xsl:call-template name="formatLineValue">
          <xsl:with-param name="value">
            <xsl:value-of select="."/>
          </xsl:with-param>
        </xsl:call-template>
      </xsl:for-each>
    </xsl:if>

    <!-- For the refusals (RFN, RFNP and RFNT),the EENN, FIN and RNN blocks, display the DCPCD child first -->
    <xsl:if test="(name() = 'RFN') or (name() = 'RFNP') or (name() = 'RFNT') or (name() = 'EENN') or (name() = 'FIN') or (name() = 'RNN')">
        <xsl:apply-templates select="DCPCD"/>
    </xsl:if>

    <!-- Display the GAZNO attribute in the first place -->
    <xsl:for-each select="./@GAZNO">
      <!-- We do not display an empty GAZNO attribute  -->
      <xsl:if test= "(. != '')">
        <xsl:call-template name="formatLineSingle">
          <xsl:with-param name="value">
            <xsl:value-of select="."/>
            <xsl:if test="../@PUBDATE">,
              <xsl:call-template name="formatDate">
                <xsl:with-param name="Date" select="../@PUBDATE"/>
              </xsl:call-template>
            </xsl:if>
          </xsl:with-param>
        </xsl:call-template>
      </xsl:if>
    </xsl:for-each>


    <!-- Special case : for the HRN block, display now the INTOFF node, and with the 833 inid label -->
    <xsl:if test="contains(name(),'HRN')">
      <xsl:for-each select="./@INTOFF">
      <xsl:element name="tr">
        <xsl:call-template name="formatLineLabel_single"/>
        <xsl:call-template name="formatLineValue_single">
          <xsl:with-param name="value">
            <xsl:value-of select="."/>
          </xsl:with-param>
        </xsl:call-template>
      </xsl:element>
      </xsl:for-each>
    </xsl:if>

    <xsl:for-each select="./@*">
      <!-- We do not display the GAZNO and PUBDATE attributes (already displayed just above)  -->
      <!-- We do not display any ALLGSI of ALLOFF attribute                                   -->
      <!-- We do not display any INTOFF attribute (the attribute is already displayed above)  -->
      <!-- We display the LICTYPE attribute at the end of the section                         -->
      <!-- We display the REGEDAT, REGRDAT or NOTDATE at the end of the section               -->
      <xsl:if test="not(contains(name(),'REGEDAT'))
                    and not(contains(name(),'GAZNO'))
                    and not(contains(name(),'PUBDATE'))
                    and not(contains(name(),'REGRDAT'))
                    and not(contains(name(),'ALLGSI'))
                    and not(contains(name(),'ALLOFF'))
                    and not(contains(name(),'INTOFF'))
                    and not(contains(name(),'LICTYPE'))
                    and not(contains(name(),'NOTDATE'))">
        <xsl:call-template name="formatLineSingle">
          <xsl:with-param name="value">
            <xsl:value-of select="."/>
          </xsl:with-param>
        </xsl:call-template>
      </xsl:if>
    </xsl:for-each>


    <!-- For the refusals (RFN, RFNP and RFNT), the EENN, FIN and RNN blocks, display all the child nodes but the DCPCD one -->
    <xsl:if test="(name() = 'RFN') or (name() = 'RFNP') or (name() = 'RFNT') or (name() = 'EENN') or (name() = 'FIN') or (name() = 'RNN')">
      <xsl:apply-templates select="*[name() != 'DCPCD']"/>
    </xsl:if>

    <!-- For all the blocks but the refusals (RFN, RFNP and RFNT), the EENN, FIN and RNN blocks, display the child nodes -->
    <xsl:if test="(name() != 'RFN') and (name() != 'RFNP') and (name() != 'RFNT') and (name() != 'EENN') and (name() != 'FIN') and (name() != 'RNN')">

      <!-- For the CURRENT block, first display the following nodes :                                                       -->
      <!-- HOLGR, CORRGR, REPGR, IMAGE, THRDMAR, SOUMARI, TYPMARI, VIENNAGR, COLCLAGR, MARDESGR, MARTRAN, MARTRGR, BASICGS  -->
      <xsl:apply-templates select="IMAGE"/>
      <xsl:apply-templates select="HOLGR"/>
      <xsl:apply-templates select="CORRGR"/>
      <xsl:apply-templates select="LCSEEGR"/>
      <xsl:apply-templates select="REPGR"/>
      <xsl:apply-templates select="PHOLGR"/>
      <xsl:apply-templates select="STDMIND"/>
      <xsl:apply-templates select="THRDMAR"/>
      <xsl:apply-templates select="SOUMARI"/>
      <xsl:apply-templates select="TYPMARI"/>
      <xsl:apply-templates select="VIENNAGR"/>
      <xsl:apply-templates select="COLCLAGR"/>
      <xsl:apply-templates select="MARDESGR"/>
      <xsl:apply-templates select="MARTRAN"/>
      <xsl:apply-templates select="MARTRGR"/>
      <xsl:apply-templates select="BASICGS"/>

      <xsl:apply-templates select="*[(name() != 'HOLGR') and (name() != 'CORRGR') and (name() != 'REPGR') and (name() != 'PHOLGR') and
                                     (name() != 'IMAGE') and (name() != 'STDMIND') and (name() != 'THRDMAR') and (name() != 'SOUMARI') and
                                     (name() != 'TYPMARI') and (name() != 'VIENNAGR') and (name() != 'COLCLAGR')and (name() != 'LCSEEGR') and
                                     (name() != 'MARDESGR') and (name() != 'MARTRAN') and (name() != 'MARTRGR') and
                                     (name() != 'BASICGS') and (name() != 'NEWREGN') ]"/>

      <!-- For the CURRENT block, display the NEWREGN after the other nodes (INTREGN is this case) node -->
      <xsl:apply-templates select="NEWREGN"/>

    </xsl:if>

    <xsl:for-each select="./@LICTYPE">

      <!-- Display the inid 793 as label -->
      <xsl:call-template name="formatLineLabel">
        <xsl:with-param name="nodename">GSCPSET</xsl:with-param>
      </xsl:call-template>

      <!-- Display the child nodes of GSCPSET -->
      <xsl:apply-templates select="../GSCPSET/*"/>
       
       
      <!-- Display the LICTYPE -->
      <xsl:call-template name="formatLineValue">
        <xsl:with-param name="value">
          <xsl:call-template name="getLicType">
            <xsl:with-param name="type">
              <xsl:value-of select="."/>
          </xsl:with-param>
          </xsl:call-template> 
          </xsl:with-param>
          <xsl:with-param name="class">
            <xsl:if test="(name(..) = 'NLCN')">
			  valueLight
			</xsl:if>
            <xsl:if test="(name(..) != 'NLCN')">
			  value
			</xsl:if>
        </xsl:with-param>
      </xsl:call-template>

      <!-- Display the LICDURTN -->
      <xsl:apply-templates select="../LICDURTN/*"/>

    </xsl:for-each>

    <xsl:if test="(name() = 'ENN') or (name() = 'EXN') or (name() = 'REN2')">
      <xsl:for-each select="./@NOTDATE">
        <xsl:call-template name="formatLineSingle">
          <xsl:with-param name="value">
            <xsl:value-of select="."/>
          </xsl:with-param>
        </xsl:call-template>
      </xsl:for-each>
    </xsl:if>
    <xsl:if test="(name() = 'CBPN') or (name() = 'CPN') or
                  (name() = 'FUN') or (name() = 'LIN') or
                  (name() = 'PCN') or (name() = 'RAN') or
                  (name() = 'EXN') or
                  (name() = 'RNN') or (name() = 'SEN')">
      <xsl:for-each select="./@REGEDAT">
        <xsl:call-template name="formatLineSingle">
          <xsl:with-param name="value">
            <xsl:value-of select="."/>
          </xsl:with-param>
        </xsl:call-template>
      </xsl:for-each>
    </xsl:if>
    <xsl:if test="(name() = 'CBNT') or (name() = 'CEN')  or (name() = 'NLCN')">
      <xsl:for-each select="./@REGRDAT">
        <xsl:call-template name="formatLineSingle">
          <xsl:with-param name="value">
            <xsl:value-of select="."/>
          </xsl:with-param>
        </xsl:call-template>
      </xsl:for-each>
    </xsl:if>

  </xsl:template>

  <!-- Default template for all nodes and attributes, from the third level and below -->
  <xsl:template match="*">

    <!-- Display the name of the element -->
    <xsl:call-template name="formatLineLabel"/>

    <!-- If present, display the text of the element -->
    <xsl:if test="text()">
      <xsl:call-template name="formatLineValue">
        <xsl:with-param name="value" select="text()"/>
        <xsl:with-param name="class">
          <!-- For the MARDESGR, COLCLAGR, MARTRAN, MARTRGR,MARTRFR,MARTREN,MARTRES,
                       TEXTEN, TEXTFR, TEXTES and FACTS nodes, display the value in light font -->
          <xsl:if test="(name(..) = 'MARDESGR') or
                        (name(..) = 'COLCLAGR') or
                        (name(.) = 'MARTRAN') or
                        (name(.) = 'MARTRGR') or
                        (name(.) = 'MARTRFR') or
                        (name(.) = 'MARTREN') or
                        (name(.) = 'MARTRES') or
                        (name(.) = 'TEXTEN') or
                        (name(.) = 'TEXTFR') or
                        (name(.) = 'TEXTES') or
                        (name(..) = 'FACTS')">
            valueLight
          </xsl:if>
          <xsl:if test="(name(..) != 'MARDESGR') and
                        (name(..) != 'COLCLAGR') and
                        (name(.) != 'MARTRAN') and
                        (name(.) != 'MARTRGR') and
                        (name(.) != 'MARTRFR') and
                        (name(.) != 'MARTREN') and
                        (name(.) != 'MARTRES') and
                        (name(.) != 'TEXTEN') and
                        (name(.) != 'TEXTFR') and
                        (name(.) != 'TEXTES') and
                        (name(..) != 'FACTS')">
            value
          </xsl:if>
        </xsl:with-param>
      </xsl:call-template>
    </xsl:if>

    <!-- Display the attributes of the element -->
    <xsl:for-each select="./@*">
      <!-- Do not display the "ORIGLAN" attribute                -->
      <!-- Do not display the "CPCD" attribute of a "NATGR" node PMI: test removed after acceptance test -->
      <!--xsl:if test="(name() != 'ORIGLAN') and not((name(..) = 'NATGR') and (name() = 'CPCD'))"-->
      <xsl:if test="(name() != 'ORIGLAN')">
        <xsl:call-template name="formatLine">
          <xsl:with-param name="value" select="."/>
        </xsl:call-template>
      </xsl:if>
    </xsl:for-each>

    <!-- Display the childs of the element -->
    <xsl:apply-templates/>

  </xsl:template>


  <!-- Specific template for the "GSHEADEN", "GSHEADFR" and "GSHEADES" nodes -->
  <xsl:template match="GSHEADEN|GSHEADFR|GSHEADES">

    <!-- Display an empty blue label for the first occurence -->
    <xsl:if test="not(contains(name(preceding-sibling::*[1]), 'GSHEAD'))">
      <xsl:call-template name="formatLineLabel">
        <xsl:with-param name="nodename">GSHEAD</xsl:with-param>
      </xsl:call-template>
    </xsl:if>

    <xsl:call-template name="formatLineValue">
      <xsl:with-param name="value" select="text()"/>
      <xsl:with-param name="class">valueLight</xsl:with-param>
    </xsl:call-template>

  </xsl:template>


  <!-- Specific template for the "GSFOOTEN", "GSFOOTFR" and "GSFOOTES" nodes -->
  <xsl:template match="GSFOOTEN|GSFOOTFR|GSFOOTES">

    <!-- Display an empty blue label for the first occurence, if the parent is not a BASICGS node -->
    <xsl:if test="not(contains(name(preceding-sibling::*[1]), 'GSFOOT')) and not(name(..) = 'BASICGS')">
      <xsl:call-template name="formatLineLabel">
        <xsl:with-param name="nodename">GSFOOT</xsl:with-param>
      </xsl:call-template>
    </xsl:if>

    <xsl:call-template name="formatLineValue">
      <xsl:with-param name="value" select="text()"/>
      <xsl:with-param name="class">valueLight</xsl:with-param>
    </xsl:call-template>

  </xsl:template>


  <!-- Specific template for the "ADDRESS" node -->
  <xsl:template match="ADDRESS">
    <xsl:for-each select="ADDRL">
      <xsl:element name="tr">
        <xsl:element name="td">
          <xsl:attribute name="width">100%</xsl:attribute>
          <xsl:attribute name="class">valueLight</xsl:attribute>
          <xsl:value-of select="text()"/>&#160;
          <xsl:if test="position()=last()">
            <xsl:element name="span">
              <xsl:attribute name="class">popup</xsl:attribute>
              (<xsl:value-of select="../COUNTRY"/>)
            </xsl:element>
          </xsl:if>
        </xsl:element>
      </xsl:element>
    </xsl:for-each>
  </xsl:template>


  <!-- Specific template for the "HOLGR", "PHOLGR", "CORRGR", "REPGR"  and "LCSEEGR" nodes -->
  <!-- We do not display any of the attributes (CLID or NOTLANG) -->
  <xsl:template match="HOLGR|PHOLGR|CORRGR|REPGR|LCSEEGR">

    <xsl:element name="tr">

      <!-- Display the name of the element -->
      <xsl:call-template name="formatLineLabel_single"/>

      <xsl:element name="td">
        <xsl:attribute name="width">*</xsl:attribute>
        <xsl:attribute name="valign">top</xsl:attribute>
        <xsl:element name="table">
          <xsl:attribute name="width">100%</xsl:attribute>
          <xsl:attribute name="cellpadding">1</xsl:attribute>
          <xsl:attribute name="cellspacing">0</xsl:attribute>

          <!-- If present, display the text of the element -->
          <xsl:if test="text()">
            <xsl:element name="tr">
              <xsl:element name="td">
                <xsl:attribute name="class">value</xsl:attribute>
                <xsl:value-of select="text()"/>
              </xsl:element>
            </xsl:element>
          </xsl:if>

          <!-- Display the childs of the element with the specific order-->
          <xsl:apply-templates select="NAME"/>
          <xsl:apply-templates select="ADDRESS"/>

        </xsl:element>
      </xsl:element>
    </xsl:element>

    <xsl:apply-templates select="ENTNATL"/>
    <xsl:apply-templates select="ENTEST"/>
    <xsl:apply-templates select="ENTDOM"/>
    <xsl:apply-templates select="*[(name() != 'NAME') and (name() != 'ADDRESS') and (name() != 'ENTNATL') and (name() != 'ENTEST') and (name() != 'ENTDOM') ]"/>

  </xsl:template>


  <!-- Specific template for the "DURTNEN", "DURTNFR" and "DURTNES" nodes -->
  <xsl:template match="DURTNEN|DURTNFR|DURTNES">
    <xsl:call-template name="formatLineValue">
      <xsl:with-param name="value">
        <xsl:call-template name="getDurationLabel"/>: <xsl:value-of select="text()"/>
      </xsl:with-param>
      <xsl:with-param name="class">valueLight</xsl:with-param>
    </xsl:call-template>
  </xsl:template>


  <!-- Specific template for the "NAME" node -->
  <xsl:template match="NAME">
    <xsl:for-each select="NAMEL">
      <xsl:element name="tr">
        <xsl:element name="td">
          <xsl:attribute name="width">100%</xsl:attribute>
          <xsl:attribute name="class">value</xsl:attribute>
          <xsl:value-of select="text()"/>
        </xsl:element>
      </xsl:element>
    </xsl:for-each>
  </xsl:template>

  <!-- Specific template for the "ENTNATL", "ENTEST", "ENTDOM" nodes -->
  <xsl:template match="ENTNATL|ENTEST|ENTDOM|NATLTY">
    <xsl:element name="tr">
      <xsl:call-template name="formatLineLabel_single"/>
      <xsl:element name="td">
        <xsl:attribute name="width">*</xsl:attribute>
        <xsl:attribute name="valign">top</xsl:attribute>
        <xsl:attribute name="class">value</xsl:attribute>
        <xsl:for-each select=".">
          <xsl:call-template name="displayCountry">
            <xsl:with-param name="countryID" select="."/>
          </xsl:call-template>
          <xsl:if test="position()!=last()"> - </xsl:if>
        </xsl:for-each>
      </xsl:element>
    </xsl:element>
  </xsl:template>

  <!-- Specific template for the "PREREGG" node -->
  <xsl:template match="PREREGG">
    <xsl:element name="tr">
      <!-- Display the name of the element -->
      <xsl:call-template name="formatLineLabel_single"/>
      <xsl:element name="td">
        <xsl:attribute name="width">*</xsl:attribute>
        <xsl:attribute name="valign">top</xsl:attribute>
        <xsl:attribute name="class">value</xsl:attribute>
        <xsl:value-of select="PREREGN"/>
        <xsl:if test="PREREGD">,
          <xsl:call-template name="formatDate">
            <xsl:with-param name="Date" select="PREREGD"/>
          </xsl:call-template>
        </xsl:if>
      </xsl:element>
    </xsl:element>
  </xsl:template>

  <!-- Specific template for the "BASICGS" nodes -->
  <xsl:template match="BASICGS">

    <xsl:element name="tr">
      <xsl:call-template name="formatLineLabel_single">
         <xsl:with-param name="append">
           <xsl:if test="@NICEVER">
           NCL(<xsl:value-of select="@NICEVER"/>)
         </xsl:if>
        </xsl:with-param>
      </xsl:call-template>
      <xsl:element name="td">
        <xsl:for-each select="GSGR">
          <xsl:element name="span">
            <xsl:attribute name="style">font-weight:bold; font-family: Arial; font-size: 9pt;color: #00518F;</xsl:attribute>
            <xsl:value-of select="@NICCLAI"/>
          </xsl:element>
          <xsl:if test="following-sibling::GSGR[1]">, </xsl:if>
        </xsl:for-each>
      </xsl:element>
    </xsl:element>

    <!-- Display the name of the element -->
    <xsl:call-template name="formatLineLabel">
       <xsl:with-param name="append">
         <xsl:if test="@NICEVER">
         NCL(<xsl:value-of select="@NICEVER"/>)
       </xsl:if>
      </xsl:with-param>
    </xsl:call-template>
    <xsl:apply-templates/>
  </xsl:template>

  <!-- Specific template for the "GSGR", "LIMTO" and "REMVD" nodes -->
  <xsl:template match="GSGR|LIMTO|REMVD|PRIGS">

    <!-- Only display the label for the first node of the list -->
    <xsl:if test="not (name(preceding-sibling::*[1]) = name())">
      <xsl:call-template name="formatLineLabel"/>
    </xsl:if>

    <xsl:element name="tr">
      <xsl:element name="td">
        <xsl:attribute name="width">40</xsl:attribute>
        <xsl:attribute name="valign">top</xsl:attribute>
        <xsl:attribute name="class">labelGS</xsl:attribute>
        <xsl:attribute name="style">text-align:right</xsl:attribute>
        <xsl:value-of select="@NICCLAI"/>
      </xsl:element>
      <xsl:element name="td">
        <xsl:attribute name="width">*</xsl:attribute>
        <xsl:attribute name="colspan">2</xsl:attribute>
        <xsl:element name="table">
          <xsl:attribute name="width">100%</xsl:attribute>
          <xsl:attribute name="cellpadding">0</xsl:attribute>
          <xsl:attribute name="cellspacing">1</xsl:attribute>
          <xsl:attribute name="class">valueLight</xsl:attribute>
          <xsl:for-each select="child::*">
            <xsl:element name="tr">
              <xsl:element name="td">
                <xsl:attribute name="width">100%</xsl:attribute>
                <xsl:attribute name="class">valueLight</xsl:attribute>
                <xsl:value-of select="."/>
              </xsl:element>
            </xsl:element>
          </xsl:for-each>
        </xsl:element>
      </xsl:element>
    </xsl:element>
  </xsl:template>


  <!-- Specific template for the "CPCD" node -->
  <xsl:template match="CPCD">
    <xsl:if test="position()=1">
      <xsl:if test="(name(..)!='INTENTG') ">
        <xsl:call-template name="formatLineLabel"/>
      </xsl:if>

      <xsl:element name="tr">
        <xsl:element name="td">
          <xsl:attribute name="width">40</xsl:attribute>
          <xsl:attribute name="valign">top</xsl:attribute>
        </xsl:element>
        <xsl:element name="td">
          <xsl:attribute name="width">*</xsl:attribute>
          <xsl:attribute name="colspan">2</xsl:attribute>
          <xsl:attribute name="class">value</xsl:attribute>
          <xsl:for-each select="../CPCD">
            <xsl:call-template name="displayCountry">
              <xsl:with-param name="countryID" select="text()"/>
            </xsl:call-template>
            <xsl:if test="following-sibling::CPCD[1]"> - </xsl:if>
          </xsl:for-each>
        </xsl:element>
      </xsl:element>
    </xsl:if>

  </xsl:template>


  <!-- Specific template for the "DCPCD" node -->
  <xsl:template match="DCPCD">

    <xsl:if test="not (preceding-sibling::DCPCD[1])">
      <xsl:element name="tr">

        <!-- If the parent is CEN or LIN, add a 833 inid code -->
        <xsl:if test="(name(..) = 'CEN') or (name(..) = 'LIN')">
          <xsl:call-template name="formatLineLabel_single">
            <xsl:with-param name="nodename">INTOFF</xsl:with-param>
          </xsl:call-template>
        </xsl:if>
        <xsl:if test="(name(..) != 'CEN') and (name(..) != 'LIN')">
          <xsl:element name="td">
            <xsl:attribute name="width">40</xsl:attribute>
            <xsl:attribute name="valign">top</xsl:attribute>
          </xsl:element>
        </xsl:if>

        <xsl:element name="td">
          <xsl:attribute name="width">*</xsl:attribute>
          <xsl:if test="(name(..) != 'CEN') and (name(..) != 'LIN')">
            <xsl:attribute name="colspan">2</xsl:attribute>
          </xsl:if>
          <xsl:attribute name="class">value</xsl:attribute>
          <xsl:for-each select="../DCPCD">
            <xsl:sort select="../DCPCD" order="ascending"/>
              <xsl:call-template name="displayCountry">
                <xsl:with-param name="countryID" select="text()"/>
              </xsl:call-template>
            <xsl:if test="following-sibling::DCPCD[1]"> - </xsl:if>
          </xsl:for-each>
        </xsl:element>

      </xsl:element>
    </xsl:if>

  </xsl:template>

  <!-- Specific template for the "VIENNAGR" nodes -->
  <xsl:template match="VIENNAGR">
    <!-- Display the name of the element -->
    <xsl:element name="tr">
      <xsl:call-template name="formatLineLabel_single">
         <xsl:with-param name="append">
          <xsl:if test="@VIENVER">
           VCL(<xsl:value-of select="@VIENVER"/>)
         </xsl:if>
       </xsl:with-param>
      </xsl:call-template>
      <xsl:apply-templates/>
    </xsl:element>
  </xsl:template>

  <!-- Specific template for the "VIECLA3" node -->
  <xsl:template match="VIECLA3">
    <xsl:if test="not (preceding-sibling::VIECLA3[1])">
      <xsl:element name="td">
        <xsl:attribute name="width">*</xsl:attribute>
        <xsl:attribute name="valign">top</xsl:attribute>
        <xsl:attribute name="class">value</xsl:attribute>
        <xsl:for-each select="../VIECLA3">
          <xsl:sort select="../VIECLA3" order="ascending"/>
	  <xsl:value-of select="substring(text(), 1, 2)"/>.<xsl:value-of select="substring(text(), 3, 2)"/>.<xsl:value-of select="substring(text(), 5, 2)"/>
          <xsl:if test="following-sibling::VIECLA3[1]"> ; </xsl:if>
        </xsl:for-each>
      </xsl:element>
    </xsl:if>
  </xsl:template>


  <!-- Specific template for the "IMAGE" node -->
  <xsl:template match="IMAGE">
    <xsl:call-template name="formatLineLabel"/>
    <xsl:element name="tr">
      <xsl:element name="td">
        <xsl:attribute name="width">40</xsl:attribute>
        <xsl:attribute name="valign">top</xsl:attribute>
      </xsl:element>
      <xsl:element name="td">
        <xsl:attribute name="width">*</xsl:attribute>
        <xsl:attribute name="colspan">2</xsl:attribute>
        <xsl:attribute name="class">value</xsl:attribute>

        <!-- if the "name" attribute is set, display the text and the image -->
        <xsl:if test="@TYPE != 'NIL'">
          <xsl:if test="@TEXT != ''">
            <xsl:element name="span">
              <xsl:attribute name="class">marklabel</xsl:attribute>
              <xsl:value-of select="@TEXT"/>
            </xsl:element>
            <br/>
          </xsl:if>
          <xsl:element name="img">
            <xsl:attribute name="src">X_IMAGE_FILENAME</xsl:attribute>
            <xsl:attribute name="typ">@NAME</xsl:attribute>
            <xsl:attribute name="style">float:left; </xsl:attribute>
          </xsl:element>
        </xsl:if>
        <!-- if the "name" attribute is not set, display the name -->
        <xsl:if test="@TYPE = 'NIL'">
          <xsl:if test="@TEXT != ''">
            <xsl:element name="span">
              <xsl:attribute name="class">marklabel</xsl:attribute>
              <xsl:value-of select="@TEXT"/>
            </xsl:element>
          </xsl:if>
          <xsl:if test="@TEXT = ''">
            No verbal elements found
          </xsl:if>
        </xsl:if>
      </xsl:element>
    </xsl:element>
  </xsl:template>


  <!-- Specific template for the "PRIGR" node -->
  <xsl:template match="PRIGR">
    <!-- Display the name of the element -->
    <xsl:call-template name="formatLineLabel"/>
    <xsl:apply-templates select="*[name() = 'PRIGS']"/>
    <xsl:element name="tr">
      <xsl:element name="td">
        <xsl:attribute name="width">40</xsl:attribute>
        <xsl:attribute name="valign">top</xsl:attribute>
      </xsl:element>
      <xsl:element name="td">
        <xsl:attribute name="width">*</xsl:attribute>
        <xsl:attribute name="class">value</xsl:attribute>
        <xsl:call-template name="displayCountry">
          <xsl:with-param name="countryID" select="PRICP"/>
        </xsl:call-template>
        <xsl:if test="PRIAPPD">,
          <xsl:call-template name="formatDate">
            <xsl:with-param name="Date" select="PRIAPPD"/>
          </xsl:call-template>
        </xsl:if>
        <xsl:if test="PRIAPPN != ''">,
          <xsl:value-of select="PRIAPPN"/>
        </xsl:if>
      </xsl:element>
    </xsl:element>
    <xsl:apply-templates select="*[name() != 'PRIGS']"/>
  </xsl:template>


  <!-- Specific template for the "BASGR" node -->
  <!-- We want first to display the BASAPPGR nodes, then the BASREGGR nodes -->
  <xsl:template match="BASGR">
    <xsl:if test="not (preceding-sibling::BASGR[1])">
      <xsl:apply-templates select="../BASGR/BASAPPGR"/>
      <xsl:apply-templates select="../BASGR/BASREGGR"/>
    </xsl:if>
  </xsl:template>


  <!-- Specific template for the "BASAPPGR" node -->
  <xsl:template match="BASAPPGR">

    <!-- If no BASAPPN do not display "BASAPPGR" node -->
    <xsl:if test="BASAPPN != ''">

    <xsl:element name="tr">

    <!-- Display the name of the element -->
    <xsl:call-template name="formatLineLabel_single"/>
      <xsl:element name="td">
        <xsl:attribute name="width">*</xsl:attribute>
        <xsl:attribute name="valign">top</xsl:attribute>
        <xsl:attribute name="class">value</xsl:attribute>
        <xsl:call-template name="displayCountry">
          <xsl:with-param name="countryID" select="/MARKGR/@OOCD"/>
        </xsl:call-template>
        <xsl:if test="BASAPPD != ''">,
          <xsl:call-template name="formatDate">
            <xsl:with-param name="Date" select="BASAPPD"/>
          </xsl:call-template>
        </xsl:if>
        <xsl:if test="BASAPPN != ''">,
          <xsl:value-of select="BASAPPN"/>
        </xsl:if>
      </xsl:element>
      <xsl:apply-templates/>

    </xsl:element>

   </xsl:if>
  </xsl:template>


  <!-- Specific template for the "BASREGGR" node -->
  <xsl:template match="BASREGGR">

    <xsl:element name="tr">

    <!-- Display the name of the element -->
    <xsl:call-template name="formatLineLabel_single"/>
      <xsl:element name="td">
        <xsl:attribute name="width">*</xsl:attribute>
        <xsl:attribute name="valign">top</xsl:attribute>
        <xsl:attribute name="class">value</xsl:attribute>
        <xsl:if test="name(../..)!='DBN'" >
        <xsl:call-template name="displayCountry">
          <xsl:with-param name="countryID" select="/MARKGR/@OOCD"/>
        </xsl:call-template>
        </xsl:if>
        <xsl:if test="(name(../..)!='DBN') and BASREGD != ''" >, </xsl:if>
        <xsl:if test="BASREGD != ''">
          <xsl:call-template name="formatDate">
            <xsl:with-param name="Date" select="BASREGD"/>
          </xsl:call-template>
        </xsl:if>
        <xsl:if test="BASREGN != ''">, <xsl:value-of select="BASREGN"/></xsl:if>
      </xsl:element>
      <xsl:apply-templates/>

    </xsl:element>

  </xsl:template>


  <!-- Specific template for the "LEGNATT" node -->
  <xsl:template match="LEGNATT">
    <xsl:element name="tr">

    <!-- Display the name of the element -->
    <xsl:call-template name="formatLineLabel_single"/>
      <xsl:element name="td">
        <xsl:attribute name="width">*</xsl:attribute>
        <xsl:attribute name="valign">top</xsl:attribute>
        <xsl:attribute name="class">value</xsl:attribute>
        <xsl:value-of select="text()"/><xsl:if test="following-sibling::PLAINCO[1]">, <xsl:value-of select="following-sibling::PLAINCO[1]"/></xsl:if>
      </xsl:element>
      <xsl:apply-templates/>

    </xsl:element>
  </xsl:template>


  <!-- Specific template for the "AFFCP" node -->
  <xsl:template match="AFFCP">
    <xsl:if test="not (preceding-sibling::AFFCP[1])">

      <!-- If the parent is CPN, add a 833 inid code -->
      <xsl:if test="(name(../..) = 'CPN')">
        <xsl:call-template name="formatLineLabel">
          <xsl:with-param name="nodename">INTOFF</xsl:with-param>
        </xsl:call-template>
      </xsl:if>

      <xsl:call-template name="formatLineLabel"/>
      <xsl:element name="tr">
        <xsl:element name="td">
          <xsl:attribute name="width">40</xsl:attribute>
          <xsl:attribute name="valign">top</xsl:attribute>
        </xsl:element>
        <xsl:element name="td">
          <xsl:attribute name="width">*</xsl:attribute>
          <xsl:attribute name="class">value</xsl:attribute>
          <xsl:for-each select="../*[@CPCD]">
            <xsl:if test="position() != 1"> - </xsl:if>
            <xsl:call-template name="displayCountry">
              <xsl:with-param name="countryID" select="@CPCD"/>
            </xsl:call-template>
          </xsl:for-each>
        </xsl:element>
      </xsl:element>
    </xsl:if>
  </xsl:template>


  <!-- Specific template for the "LICDCPCD" node -->
  <xsl:template match="LICDCPCD">
    <xsl:if test="not(name(preceding-sibling::*[1]) = 'LICDCPCD')">
      <xsl:call-template name="formatLineLabel"/>
      <xsl:element name="tr">
        <xsl:element name="td">
          <xsl:attribute name="width">40</xsl:attribute>
          <xsl:attribute name="valign">top</xsl:attribute>
        </xsl:element>
        <xsl:element name="td">
          <xsl:attribute name="width">*</xsl:attribute>
          <xsl:attribute name="class">value</xsl:attribute>
          <xsl:for-each select="../LICDCPCD/DCPCD">
            <xsl:sort select="../LICDCPCD/DCPCD" order="ascending"/>
            <xsl:call-template name="displayCountry">
              <xsl:with-param name="countryID" select="text()"/>
            </xsl:call-template>
            <xsl:if test="../following-sibling::LICDCPCD[1]"> - </xsl:if>
          </xsl:for-each>
        </xsl:element>
      </xsl:element>
    </xsl:if>
  </xsl:template>


  <!-- Specific template for the "INTREGG" node -->
  <xsl:template match="INTREGG">

    <!-- Only display the last INTREGG -->
    <xsl:if test="not (following-sibling::INTREGG[1])">

      <!-- Do not display the MARKVE -->
      <xsl:apply-templates select="*[name() != 'MARKVE']"/>

    </xsl:if>
  </xsl:template>


  <!-- Specific template for the "INTREGN" node -->
  <xsl:template match="INTREGN">
    <xsl:call-template name="formatLineSingle">
      <xsl:with-param name="value">

        <!-- If there is a NEWREGN node before the INTREGG parent node, display the NEWREGN value -->
        <xsl:if test="name(../preceding-sibling::*[1]) = 'NEWREGN'">
          <xsl:call-template name="removeZerosAndTruncate">
            <xsl:with-param name="str"><xsl:value-of select="../preceding-sibling::*[1]"/></xsl:with-param>
            <xsl:with-param name="startIndex">-1</xsl:with-param>
            <xsl:with-param name="strLength">-1</xsl:with-param>
          </xsl:call-template> ;
        </xsl:if>

        <xsl:call-template name="removeZerosAndTruncate">
          <xsl:with-param name="str"><xsl:value-of select="."/></xsl:with-param>
          <xsl:with-param name="startIndex">-1</xsl:with-param>
          <xsl:with-param name="strLength">-1</xsl:with-param>
        </xsl:call-template>
      </xsl:with-param>
    </xsl:call-template>
  </xsl:template>

<!-- Specific template for the "NATGR" node -->
  <xsl:template match="NATGR">

      <!-- If the parent is FBN, add a 833 inid code -->
      <xsl:if test="(name(..) = 'FBN')">

      <xsl:call-template name="formatLineLabel">
          <xsl:with-param name="nodename">NATGR</xsl:with-param>
      </xsl:call-template>

        <xsl:call-template name="formatLineValue" >
          <xsl:with-param name="value">
           <xsl:call-template name="formatDate">
              <xsl:with-param name="Date" select="./NATRDAT"/>
            </xsl:call-template>,
            <xsl:value-of select="./NATRNUM"/>
          </xsl:with-param>
          <xsl:with-param name="country">
               <xsl:value-of select="@CPCD"/>
           </xsl:with-param>
        </xsl:call-template>
      </xsl:if>
      
      <!-- Do not display the NATFDAT -->
      <xsl:apply-templates select="*[name() != 'NATFDAT' and name() != 'NATRDAT' and name() != 'NATRNUM']"/>
  
  </xsl:template>  
  
  <!-- Specific template for the "NEWREGN" node -->
  <xsl:template match="NEWREGN">
    <xsl:call-template name="formatLineSingle">
      <xsl:with-param name="value">
        <xsl:call-template name="removeZerosAndTruncate">
          <xsl:with-param name="str"><xsl:value-of select="."/></xsl:with-param>
          <xsl:with-param name="startIndex">-1</xsl:with-param>
          <xsl:with-param name="strLength">-1</xsl:with-param>
        </xsl:call-template>
      </xsl:with-param>
    </xsl:call-template>
  </xsl:template>


  <!-- Specific template for the "SOUMARI" node -->
  <xsl:template match="SOUMARI">
    <xsl:call-template name="formatLineSingle">
      <xsl:with-param name="value">
        <xsl:call-template name="getSOUMARILabel"/>
      </xsl:with-param>
    </xsl:call-template>
  </xsl:template>


  <!-- Specific template for the "THRDMAR" node -->
  <xsl:template match="THRDMAR">
    <xsl:call-template name="formatLineSingle">
      <xsl:with-param name="value">
        <xsl:call-template name="getTHRDMARLabel"/>
      </xsl:with-param>
    </xsl:call-template>
  </xsl:template>


  <!-- Specific template for the "TYPMARI" node -->
  <xsl:template match="TYPMARI">
    <xsl:call-template name="formatLineSingle">
      <xsl:with-param name="value">
        <xsl:call-template name="getTYPMARILabel">
          <xsl:with-param name="value"><xsl:value-of select="."/></xsl:with-param>
        </xsl:call-template>
      </xsl:with-param>
    </xsl:call-template>
  </xsl:template>

  <xsl:template match="text()|MARDUR|PRICP|PRIAPPD|PRIAPPN|BASAPPD|BASAPPN|BASREGD|BASREGN|PLAINCO|REFDAT|OPPERS|GSCPSET|LICDURTN|VIECLAI|DISCLAIMGR|SIGVRBL|VRBLNOT|ENTADDR">
  </xsl:template>

  <!-- Template for Date formatting -->
  <xsl:template name="formatDate">
    <xsl:param name="Date"/>
    <xsl:value-of select="concat(substring($Date,7,2),'.',substring($Date, 5,2),'.',substring($Date, 1,4))"/>
  </xsl:template>

  <!-- Template for displaying a line with a label and a value -->
  <xsl:template name="formatLineSingle">
    <xsl:param name="value"/>
    <xsl:element name="tr">
      <xsl:call-template name="formatLineLabel_single"/>
      <xsl:call-template name="formatLineValue_single">
        <xsl:with-param name="value" select="$value"/>
      </xsl:call-template>
    </xsl:element>
  </xsl:template>

  <!-- Template for displaying a line with a label and a value -->
  <xsl:template name="formatLine">
    <xsl:param name="value"/>
    <xsl:call-template name="formatLineLabel"/>
    <xsl:call-template name="formatLineValue">
      <xsl:with-param name="value" select="$value"/>
    </xsl:call-template>
  </xsl:template>

  <!-- Template for displaying a value without the TR tags -->
  <xsl:template name="formatLineValue_single">
    <xsl:param name="value"/>
    <xsl:param name="class">value</xsl:param>
    <xsl:param name="country"></xsl:param>
    <xsl:element name="td">
      <xsl:attribute name="width">*</xsl:attribute>
      <xsl:attribute name="valign">top</xsl:attribute>
      <xsl:attribute name="class"><xsl:value-of select="$class"/></xsl:attribute>
      <xsl:choose>
        <xsl:when test="contains(name(),'REGEDAT') or contains(name(),'NOTDATE') or
                        contains(name(),'NATPDAT') or contains(name(),'OPPERE') or
                        contains(name(),'NATRDAT') or contains(name(),'INTREGD') or
                        contains(name(),'EXPDATE') or contains(name(),'BASAPPD') or
                        contains(name(),'BASREGD') or contains(name(),'NATFDAT') or
                        contains(name(),'REGRDAT') or contains(name(),'PUBDATE')">
          <xsl:call-template name="formatDate">
            <xsl:with-param name="Date" select="$value"/>
          </xsl:call-template>
        </xsl:when>
        <xsl:when test="contains(name(),'ENTNATL') or
                        contains(name(),'ENTEST') or
                        contains(name(),'ENTDOM') or
                        contains(name(),'INTOFF') or
                        contains(name(),'OOCD')">
          <xsl:element name="span">
            <xsl:attribute name="class">popup</xsl:attribute>
            <xsl:attribute name="onclick">javascript:displayCountry('<xsl:value-of select="$value"/>');</xsl:attribute>
            <xsl:choose>
              <xsl:when test="text()">
                <xsl:value-of select="text()"/>
              </xsl:when>
              <xsl:otherwise>
                <xsl:value-of select="."/>
              </xsl:otherwise>
            </xsl:choose>
          </xsl:element>
        </xsl:when>
        <xsl:otherwise>
          <xsl:value-of select="$value"/>
             <xsl:if test="$country">,
             <xsl:call-template name="displayCountry">
                 <xsl:with-param name="countryID" select="$country" />
              </xsl:call-template>
             </xsl:if>
        </xsl:otherwise>
      </xsl:choose>
    </xsl:element>
  </xsl:template>


  <!-- Template for displaying a value -->
  <xsl:template name="formatLineValue">
    <xsl:param name="value"/>
    <xsl:param name="class">value</xsl:param>
    <xsl:param name="country"></xsl:param>
    <xsl:element name="tr">
      <xsl:element name="td">
        <xsl:attribute name="width">40</xsl:attribute>
        <xsl:attribute name="valign">top</xsl:attribute>
      </xsl:element>
      <xsl:element name="td">
        <xsl:attribute name="colspan">2</xsl:attribute>
        <xsl:attribute name="width">*</xsl:attribute>
        <xsl:attribute name="class"><xsl:value-of select="$class"/></xsl:attribute>
        <xsl:choose>
          <xsl:when test="contains(name(),'REGEDAT') or contains(name(),'NOTDATE') or
                          contains(name(),'NATPDAT') or contains(name(),'OPPERE') or
                          contains(name(),'NATRDAT') or contains(name(),'INTREGD') or
                          contains(name(),'EXPDATE') or contains(name(),'BASAPPD') or
                          contains(name(),'BASREGD') or contains(name(),'NATFDAT') or
                          contains(name(),'REGRDAT') or contains(name(),'PUBDATE')">
            <xsl:call-template name="formatDate">
              <xsl:with-param name="Date" select="$value"/>
            </xsl:call-template>
          </xsl:when>
          <xsl:when test="contains(name(),'ENTNATL') or
                          contains(name(),'ENTEST') or
                          contains(name(),'ENTDOM') or
                          contains(name(),'INTOFF') or
                          contains(name(),'OOCD')">
            <xsl:element name="span">
              <xsl:attribute name="class">popup</xsl:attribute>
              <xsl:choose>
                <xsl:when test="text()">
                  <xsl:value-of select="text()"/>
                </xsl:when>
                <xsl:otherwise>
                  <xsl:value-of select="."/>
                </xsl:otherwise>
              </xsl:choose>
            </xsl:element>
          </xsl:when>
          <xsl:otherwise>
            <xsl:value-of select="$value"/>
               <xsl:if test="$country">,
               <xsl:call-template name="displayCountry">
                   <xsl:with-param name="countryID" select="$country" />
                </xsl:call-template>
               </xsl:if>
          </xsl:otherwise>
        </xsl:choose>
      </xsl:element>
    </xsl:element>
  </xsl:template>


  <!-- Template for displaying the initials of a country -->
  <xsl:template name="displayCountry">
    <xsl:param name="countryID"/>
    <xsl:element name="span">
      <xsl:attribute name="class">popup</xsl:attribute>
      <xsl:value-of select="$countryID"/>
    </xsl:element>
  </xsl:template>


  <!-- Template for removing zeros at the beginning of a string and to truncate
  the remaining part -->
  <xsl:template name="removeZerosAndTruncate">
    <xsl:param name="str"/>
    <xsl:param name="startIndex"/>
    <xsl:param name="strLength"/>

    <xsl:if test="not(starts-with($str, '0'))">
      <xsl:if test="$startIndex != -1">
        <xsl:value-of select="substring($str, $startIndex, $strLength)"/>
      </xsl:if>
      <xsl:if test="$startIndex = -1">
        <xsl:value-of select="$str"/>
      </xsl:if>
    </xsl:if>
    <xsl:if test="starts-with($str, '0')">
      <xsl:call-template name="removeZerosAndTruncate">
        <xsl:with-param name="str">
          <xsl:value-of select="substring($str, 2, string-length($str)-1)"/>
        </xsl:with-param>
        <xsl:with-param name="startIndex"><xsl:value-of select="$startIndex"/></xsl:with-param>
        <xsl:with-param name="strLength"><xsl:value-of select="$strLength"/></xsl:with-param>
      </xsl:call-template>
    </xsl:if>

  </xsl:template>

</xsl:stylesheet>
                                                                      

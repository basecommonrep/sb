<?xml version='1.0' encoding="UTF-8"?>
<!-- Copyright 2004 ELCA Informatique -->

<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

  <xsl:variable name="inidFile" select="document('./inid.xml')"/>

  <!-- define key from the "Label" Element of the Inid root element -->
  <xsl:key name="INID" match="//Inid" use="Label" />

  <xsl:template name="formatLineLabel_single">
    <xsl:param name="class">labelTable</xsl:param>
    <xsl:param name="classinid">labelINID</xsl:param>
    
    <xsl:param name="nodename"><xsl:value-of select="name()"/></xsl:param>
    <xsl:param name="append"></xsl:param>

    <!-- The nodepath variable will be used when the corresponding INID can take different -->
    <!-- values for its Id and Description, depending on the location of the node in the   -->
    <!-- XML document. -->
    <xsl:variable name="nodepath">
      <xsl:for-each select="ancestor::*">/<xsl:value-of select="name()"/></xsl:for-each>
    </xsl:variable>

    <!-- First we have to make sure that the inid is defined in the list -->
    <xsl:for-each select="$inidFile" >
      <xsl:choose>

        <xsl:when test="key('INID',$nodename) or contains($class, 'labelBlock')">
          <!-- The inid was found in the list -->
            <xsl:element name="td">
              <xsl:attribute name="width">40</xsl:attribute>
              <xsl:attribute name="valign">top</xsl:attribute>
<!--              <xsl:element name="table">
                <xsl:attribute name="width">100%</xsl:attribute>
                <xsl:attribute name="cellpadding">2</xsl:attribute>
                <xsl:attribute name="cellspacing">1</xsl:attribute>
                <xsl:element name="td">
                  <xsl:attribute name="valign">top</xsl:attribute> -->
                  <xsl:attribute name="class"><xsl:value-of select="$classinid"/></xsl:attribute>
                  <xsl:call-template name="getInidValue">
                    <xsl:with-param name="nodename" select="$nodename"/>
                    <xsl:with-param name="nodepath" select="$nodepath"/>
                    <xsl:with-param name="type">Id</xsl:with-param>
                  </xsl:call-template>
<!--                </xsl:element>
              </xsl:element> -->
            </xsl:element>
            <xsl:element name="td">
              <xsl:attribute name="width">40%</xsl:attribute>
              <xsl:attribute name="valign">top</xsl:attribute>
<!--              <xsl:element name="table">
                <xsl:attribute name="width">100%</xsl:attribute>
                <xsl:attribute name="cellpadding">2</xsl:attribute>
                <xsl:attribute name="cellspacing">1</xsl:attribute>
                <xsl:element name="td">
                  <xsl:attribute name="valign">top</xsl:attribute> -->
                  <xsl:attribute name="class"><xsl:value-of select="$class"/></xsl:attribute>
                  <xsl:call-template name="getInidValue">
                    <xsl:with-param name="nodename" select="$nodename"/>
                    <xsl:with-param name="nodepath" select="$nodepath"/>
                    <xsl:with-param name="type">Description</xsl:with-param>
                  </xsl:call-template>
                  <xsl:if test="$append!=''"> - <xsl:value-of select="$append"/>
                  </xsl:if>
<!--                </xsl:element>
              </xsl:element> -->
            </xsl:element>
        </xsl:when>

        <xsl:otherwise>
        <!-- The inid wasn't found in the list => Don't display anything -->
          <xsl:element name="td">
            <xsl:attribute name="colspan">2</xsl:attribute>
            <xsl:attribute name="valign">top</xsl:attribute>
            &#160;
          </xsl:element>
        </xsl:otherwise>

        </xsl:choose>
      </xsl:for-each>

    </xsl:template>

  <xsl:template name="formatLineLabel">
    <xsl:param name="class">labelTable</xsl:param>
    <xsl:param name="classinid">labelINID</xsl:param>

    <xsl:param name="nodename"><xsl:value-of select="name()"/></xsl:param>
    <xsl:param name="append"></xsl:param>

    <!-- The nodepath variable will be used when the corresponding INID can take different -->
    <!-- values for its Id and Description, depending on the location of the node in the   -->
    <!-- XML document. -->
    <xsl:variable name="nodepath">
      <xsl:for-each select="ancestor::*">/<xsl:value-of select="name()"/></xsl:for-each>
    </xsl:variable>

    <!-- First we have to make sure that the inid is defined in the list -->
    <xsl:for-each select="$inidFile" >
      <xsl:choose>

        <xsl:when test="key('INID',$nodename) or contains($class, 'labelBlock')">
          <!-- The inid was found in the list -->
          <xsl:element name="tr">
            <xsl:element name="td">
              <xsl:attribute name="width">40</xsl:attribute>
              <xsl:attribute name="valign">top</xsl:attribute>
<!--              <xsl:element name="table">
                <xsl:attribute name="width">100%</xsl:attribute>
                <xsl:attribute name="cellpadding">2</xsl:attribute>
                <xsl:attribute name="cellspacing">1</xsl:attribute>
                <xsl:element name="td">
                  <xsl:attribute name="valign">top</xsl:attribute> -->
                  <xsl:attribute name="class"><xsl:value-of select="$classinid"/></xsl:attribute>
                  <xsl:call-template name="getInidValue">
                    <xsl:with-param name="nodename" select="$nodename"/>
                    <xsl:with-param name="nodepath" select="$nodepath"/>
                    <xsl:with-param name="type">Id</xsl:with-param>
                  </xsl:call-template>
<!--                </xsl:element>
              </xsl:element> -->
            </xsl:element>
            <xsl:element name="td">
              <xsl:attribute name="width">*</xsl:attribute>
              <xsl:attribute name="colspan">2</xsl:attribute>
<!--              <xsl:element name="table">
                <xsl:attribute name="width">100%</xsl:attribute>
                <xsl:attribute name="cellpadding">2</xsl:attribute>
                <xsl:attribute name="cellspacing">1</xsl:attribute>
                <xsl:element name="td"> -->
                  <xsl:attribute name="class"><xsl:value-of select="$class"/></xsl:attribute>
                  <xsl:call-template name="getInidValue">
                    <xsl:with-param name="nodename" select="$nodename"/>
                    <xsl:with-param name="nodepath" select="$nodepath"/>
                    <xsl:with-param name="type">Description</xsl:with-param>
                  </xsl:call-template>
                  <xsl:if test="$append!=''"> - <xsl:value-of select="$append"/>
                  </xsl:if>
<!--                </xsl:element>
              </xsl:element> -->
            </xsl:element>
          </xsl:element>
        </xsl:when>

        <xsl:otherwise>
        <!-- The inid wasn't found in the list => Don't display anything -->
        </xsl:otherwise>

        </xsl:choose>
      </xsl:for-each>

    </xsl:template>


    <!-- getInidValue template  -->
    <xsl:template name="getInidValue">

      <xsl:param name="nodename" />
      <xsl:param name="nodepath" />
      <xsl:param name="type" />

      <xsl:for-each select="$inidFile" >

        <!-- Look for the corresponding nodename in the inidFile -->
        <xsl:choose>

          <!-- if the nodename is present in one inid (default case), simply display it -->
          <xsl:when test="count(key('INID',$nodename)) = 1">
            <xsl:if test="$type = 'Id'">
              <xsl:choose>
                <xsl:when test="key('INID',$nodename)/Id != '&#160;'">
                  (<xsl:value-of select="key('INID',$nodename)/Id"/>)
                </xsl:when>
                <xsl:otherwise>
                  <xsl:value-of select="key('INID',$nodename)/Id"/>
                </xsl:otherwise>
              </xsl:choose>
            </xsl:if>
            <xsl:if test="$type = 'Description'">
              <xsl:if test="key('INID',$nodename)/Description[@language=$language]">
                <xsl:value-of select="key('INID',$nodename)/Description[@language=$language]"/>
              </xsl:if>
              <xsl:if test=" not (key('INID',$nodename)/Description[@language=$language])">
                <xsl:value-of select="key('INID',$nodename)/Description[@language='en']"/>
              </xsl:if>
            </xsl:if>
          </xsl:when>

          <!-- if the nodename is present in more that one inid, use the Ancestors node -->
          <xsl:when test="count(key('INID',$nodename)) &gt; 1">

            <!-- Look for the Inid with matching ancestors -->
            <xsl:for-each select="key('INID', $nodename)[contains($nodepath, Ancestors)][1]">
              <xsl:if test="$type = 'Id'">
                <xsl:choose>
                  <xsl:when test="Id != '&#160;'">
                    (<xsl:value-of select="Id"/>)
                  </xsl:when>
                  <xsl:otherwise>
                    <xsl:value-of select="Id"/>
                  </xsl:otherwise>
                </xsl:choose>
              </xsl:if>
              <xsl:if test="$type = 'Description'">
                <xsl:if test="Description[@language=$language]">
                  <xsl:value-of select="Description[@language=$language]"/>
                </xsl:if>
                <xsl:if test=" not (Description[@language=$language])">
                  <xsl:value-of select="Description[@language='en']"/>
                </xsl:if>
              </xsl:if>
            </xsl:for-each>

	        </xsl:when>

          <!-- Otherwise simply output the nodename when the label in not present -->
          <xsl:otherwise>
            <xsl:value-of select="$nodename"/>
          </xsl:otherwise>

        </xsl:choose>

      </xsl:for-each>

    </xsl:template>

</xsl:stylesheet>

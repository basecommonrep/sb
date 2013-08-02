<?xml version='1.0' encoding="UTF-8"?>
<!-- Copyright 2004 ELCA Informatique -->

<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">


    <xsl:template name="getNavigationLabel">
      <xsl:param name="label"/>    
      <xsl:choose>
        <xsl:when test="$label = 'title'">
          <xsl:choose>
            <xsl:when test="$language = 'en'">Registration Details</xsl:when>
            <xsl:when test="$language = 'fr'">Détails de l'enregistrement</xsl:when>
            <xsl:when test="$language = 'es'">Detalles del registro</xsl:when>
          </xsl:choose>
        </xsl:when>
        <xsl:when test="$label = 'view'">
          <xsl:choose>
            <xsl:when test="$language = 'en'">View</xsl:when>
            <xsl:when test="$language = 'fr'">Afficher</xsl:when>
            <xsl:when test="$language = 'es'">Vista</xsl:when>
          </xsl:choose>
        </xsl:when>
        <xsl:when test="$label = 'details'">
          <xsl:choose>
            <xsl:when test="$language = 'en'">Full details</xsl:when>
            <xsl:when test="$language = 'fr'">Détail</xsl:when>
            <xsl:when test="$language = 'es'">Detalles</xsl:when>
          </xsl:choose>
        </xsl:when>
        <xsl:when test="$label = 'summaryview'">
          <xsl:choose>
            <xsl:when test="$language = 'en'">Summary</xsl:when>
            <xsl:when test="$language = 'fr'">Résumé</xsl:when>
            <xsl:when test="$language = 'es'">Resumen</xsl:when>
          </xsl:choose>
        </xsl:when>
        <xsl:when test="$label = 'countries'">
          <xsl:choose>
            <xsl:when test="$language = 'en'">Countries</xsl:when>
            <xsl:when test="$language = 'fr'">Pays</xsl:when>
            <xsl:when test="$language = 'es'">Países</xsl:when>
          </xsl:choose>
        </xsl:when>
        <xsl:when test="$label = 'shortcuts'">
          <xsl:choose>
            <xsl:when test="$language = 'en'">Shortcuts</xsl:when>
            <xsl:when test="$language = 'fr'">Raccourcis</xsl:when>
            <xsl:when test="$language = 'es'">Enlaces</xsl:when>
          </xsl:choose>
        </xsl:when>
        <xsl:when test="$label = 'printpreview'">
          <xsl:choose>
            <xsl:when test="$language = 'en'">Print preview</xsl:when>
            <xsl:when test="$language = 'fr'">Prévisualisation</xsl:when>
            <xsl:when test="$language = 'es'">Vista preliminar</xsl:when>
          </xsl:choose>
        </xsl:when>
        <xsl:when test="$label = 'print'">
          <xsl:choose>
            <xsl:when test="$language = 'en'">Print</xsl:when>
            <xsl:when test="$language = 'fr'">Imprimer</xsl:when>
            <xsl:when test="$language = 'es'">Imprimir</xsl:when>
          </xsl:choose>
        </xsl:when>
        <xsl:when test="$label = 'eventssummary'">
          <xsl:choose>
            <xsl:when test="$language = 'en'">History Summary</xsl:when>
            <xsl:when test="$language = 'fr'">Résumé de l'historique</xsl:when>
            <xsl:when test="$language = 'es'">Resumen del historial</xsl:when>
          </xsl:choose>
        </xsl:when>
      </xsl:choose>
    </xsl:template>


    <xsl:template name="getLanguageFromID">
      <xsl:param name="langID"/>    
      <xsl:choose>
        <xsl:when test="$langID = '1'">
          <xsl:choose>
            <xsl:when test="$language = 'en'">English</xsl:when>
            <xsl:when test="$language = 'fr'">Anglais</xsl:when>
            <xsl:when test="$language = 'es'">Inglés</xsl:when>
          </xsl:choose>
        </xsl:when>
        <xsl:when test="$langID = '3'">
          <xsl:choose>
            <xsl:when test="$language = 'en'">French</xsl:when>
            <xsl:when test="$language = 'fr'">Français</xsl:when>
            <xsl:when test="$language = 'es'">Francés</xsl:when>
          </xsl:choose>
        </xsl:when>
        <xsl:when test="$langID = '4'">
          <xsl:choose>
            <xsl:when test="$language = 'en'">Spanish</xsl:when>
            <xsl:when test="$language = 'fr'">Espagnol</xsl:when>
            <xsl:when test="$language = 'es'">Español</xsl:when>
          </xsl:choose>
        </xsl:when>
      </xsl:choose>
    </xsl:template>


    <xsl:template name="getLicType">
      <xsl:param name="type"/>    
      <xsl:choose>
        <xsl:when test="$type = 'EX'">
          <xsl:choose>
            <xsl:when test="$language = 'en'">Exclusive licence</xsl:when>
            <xsl:when test="$language = 'fr'">Licence exclusive</xsl:when>
            <xsl:when test="$language = 'es'">Licencia exclusiva</xsl:when>
          </xsl:choose>
        </xsl:when>
        <xsl:when test="$type = 'SO'">
          <xsl:choose>
            <xsl:when test="$language = 'en'">Sole licence</xsl:when>
            <xsl:when test="$language = 'fr'">Licence unique</xsl:when>
            <xsl:when test="$language = 'es'">Licencia única</xsl:when>
          </xsl:choose>
        </xsl:when>
        <xsl:when test="$type = 'PL'">
          <xsl:choose>
            <xsl:when test="$language = 'en'">Plain licence</xsl:when>
            <xsl:when test="$language = 'fr'">Licence simple</xsl:when>
            <xsl:when test="$language = 'es'">Licencia simple</xsl:when>
          </xsl:choose>
        </xsl:when>
      </xsl:choose>
    </xsl:template>


    <xsl:template name="getDurationLabel">
      <xsl:choose>
        <xsl:when test="$language = 'en'">Duration</xsl:when>
        <xsl:when test="$language = 'fr'">Durée</xsl:when>
        <xsl:when test="$language = 'es'">Duración</xsl:when>
      </xsl:choose>
    </xsl:template>


    <xsl:template name="getSOUMARILabel">
      <xsl:choose>
        <xsl:when test="$language = 'en'">Sound mark</xsl:when>
        <xsl:when test="$language = 'fr'">Marque sonore</xsl:when>
        <xsl:when test="$language = 'es'">Marca de sonido</xsl:when>
      </xsl:choose>
    </xsl:template>


    <xsl:template name="getTHRDMARLabel">
      <xsl:choose>
        <xsl:when test="$language = 'en'">Three-dimensional mark</xsl:when>
        <xsl:when test="$language = 'fr'">Marque tridimensionnelle</xsl:when>
        <xsl:when test="$language = 'es'">Marca tridimensional</xsl:when>
      </xsl:choose>
    </xsl:template>


    <xsl:template name="getTYPMARILabel">
      <xsl:param name="value"/>    
      <xsl:choose>
        <xsl:when test="$value = 'C'">
          <xsl:choose>
            <xsl:when test="$language = 'en'">Collective mark</xsl:when>
            <xsl:when test="$language = 'fr'">Marque collective</xsl:when>
            <xsl:when test="$language = 'es'">Marca colectiva</xsl:when>
          </xsl:choose>
        </xsl:when>
        <xsl:when test="$value = 'R'">
          <xsl:choose>
            <xsl:when test="$language = 'en'">Certificate mark</xsl:when>
            <xsl:when test="$language = 'fr'">Marque de certification</xsl:when>
            <xsl:when test="$language = 'es'">Marca de certificación</xsl:when>
          </xsl:choose>
        </xsl:when>
        <xsl:when test="$value = 'G'">
          <xsl:choose>
            <xsl:when test="$language = 'en'">Guarantee mark</xsl:when>
            <xsl:when test="$language = 'fr'">Marque de garantie</xsl:when>
            <xsl:when test="$language = 'es'">Marca de garantía</xsl:when>
          </xsl:choose>
        </xsl:when>
        <xsl:when test="$value = 'X'">
          <xsl:choose>
            <xsl:when test="$language = 'en'">Collective mark, certicate mark or guarantee mark</xsl:when>
            <xsl:when test="$language = 'fr'">Marque collective, de certification ou de garantie</xsl:when>
            <xsl:when test="$language = 'es'">Marca colectiva, de certificación o de garantía</xsl:when>
          </xsl:choose>
        </xsl:when>
      </xsl:choose>
    </xsl:template>

</xsl:stylesheet>

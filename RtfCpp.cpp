/*
Copyright (c) <year> <copyright holders>

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
    THE SOFTWARE.
*/
#include "StdAfx.h"
#include "RtfCpp.h"
#include <iostream>
#include <sstream>

RtfWriter::RtfWriter(const std::wstring& filename): _rtfFile(NULL), _filename(filename)
{

}

RtfWriter::~RtfWriter()
{
    if(_rtfFile)
    {
        // Write RTF document end part
        std::string rtfText ("\n\\par}");
        fwrite(rtfText.c_str(), 1, rtfText.length(), _rtfFile );

        // Close RTF document
        fclose(_rtfFile);
    }
}

bool RtfWriter::open(char* fonts, char* colors)
{
    // Set error flag
    int error = RTF_SUCCESS;

    // Initialize global params
    init();

    // Set RTF document font table
    if ( fonts != NULL )
    {
        if ( strcmp( fonts, "" ) != 0 )
            set_fonttable(fonts);
    }

    // Set RTF document color table
    if ( colors != NULL )
    {
        if ( strcmp( colors, "" ) != 0 )
            set_colortable(colors);
    }

    // Create RTF document
    char* filename = NULL;
    errno_t isOk = _wfopen_s(&_rtfFile, _filename.c_str(), L"w");
    if(isOk != 0)
        return false;
    //_rtfFile = fopen(filename, "w" );

    if ( _rtfFile != NULL )
    {
        // Write RTF document header
        if ( !write_header() )
            error = RTF_HEADER_ERROR;

        // Write RTF document formatting properties
        if ( !write_documentformat() )
            error = RTF_DOCUMENTFORMAT_ERROR;

        // Create first RTF document section with default formatting
        write_sectionformat();
    }
    else
        error = RTF_OPEN_ERROR;

    // Return error flag
    return error == RTF_SUCCESS;
}

// Writes RTF document header
bool RtfWriter::write_header()
{
    // Set error flag
    bool result = true;

    // Standard RTF document header
    std::string rtfText;
    rtfText += "{\\rtf1\\ansi\\ansicpg1252\\deff0{\\fonttbl";
    rtfText += _rtfFontTable;
    rtfText += "}{\\colortbl";
    rtfText += _rtfColorTable;
    rtfText += "}{\\*\\generator rtflib ver. 1.0;}";
    rtfText += "\n{\\info{\\author rtflib ver. 1.0}{\\company ETC Company LTD.}}";

    // Writes standard RTF document header part
    if ( fwrite( rtfText.c_str(), 1, rtfText.length(), _rtfFile ) < rtfText.length() )
        result = false;

    // Return error flag
    return result;
}

void RtfWriter::init()
{
    // Set RTF document default font table
     _rtfFontTable.clear();
    _rtfFontTable += "{\\f0\\froman\\fcharset0\\cpg1252 Times New Roman}";
    _rtfFontTable += "{\\f1\\fswiss\\fcharset0\\cpg1252 Arial}";
    _rtfFontTable += "{\\f2\\fmodern\\fcharset0\\cpg1252 Courier New}";
    _rtfFontTable += "{\\f3\\fscript\\fcharset0\\cpg1252 Cursive}";
    _rtfFontTable += "{\\f4\\fdecor\\fcharset0\\cpg1252 Old English}";
    _rtfFontTable += "{\\f5\\ftech\\fcharset0\\cpg1252 Symbol}";
    _rtfFontTable += "{\\f6\\fbidi\\fcharset0\\cpg1252 Miriam}";

    // Set RTF document default color table
    _rtfColorTable.clear();
    _rtfColorTable += "\\red0\\green0\\blue0;" ;
    _rtfColorTable += "\\red255\\green0\\blue0;" ;
    _rtfColorTable += "\\red0\\green255\\blue0;" ;
    _rtfColorTable += "\\red0\\green0\\blue255;" ;
    _rtfColorTable += "\\red255\\green255\\blue0;" ;
    _rtfColorTable += "\\red255\\green0\\blue255;" ;
    _rtfColorTable += "\\red0\\green255\\blue255;" ;
    _rtfColorTable += "\\red255\\green255\\blue255;" ;
    _rtfColorTable += "\\red128\\green0\\blue0;" ;
    _rtfColorTable += "\\red0\\green128\\blue0;" ;
    _rtfColorTable += "\\red0\\green0\\blue128;" ;
    _rtfColorTable += "\\red128\\green128\\blue0;" ;
    _rtfColorTable += "\\red128\\green0\\blue128;" ;
    _rtfColorTable += "\\red0\\green128\\blue128;" ;
     _rtfColorTable += "\\red128\\green128\\blue128;" ;

    // Set default formatting
    set_defaultformat();
}

// Sets default RTF document formatting
void RtfWriter::set_defaultformat()
{
    // Set default RTF document formatting properties
    RTF_DOCUMENT_FORMAT df = {RTF_DOCUMENTVIEWKIND_PAGE, 100, 12240, 15840, 1800, 1800, 1440, 1440, false, 0, false};
    set_documentformat(&df);

    // Set default RTF section formatting properties
    RTF_SECTION_FORMAT sf = {RTF_SECTIONBREAK_CONTINUOUS, false, true, 12240, 15840, 1800, 1800, 1440, 1440, 0, 720, 720, false, 720, 720, false, 1, 720, false};
    set_sectionformat(&sf);

    // Set default RTF paragraph formatting properties
    RTF_PARAGRAPH_FORMAT pf = {RTF_PARAGRAPHBREAK_NONE, false, true, RTF_PARAGRAPHALIGN_LEFT, 0, 0, 0, 0, 0, 0, "", false, false, false, false, false, false};
    pf.BORDERS.borderColor = 0;
    pf.BORDERS.borderKind = RTF_PARAGRAPHBORDERKIND_NONE;
    pf.BORDERS.borderSpace = 0;
    pf.BORDERS.borderType = RTF_PARAGRAPHBORDERTYPE_STHICK;
    pf.BORDERS.borderWidth = 0;
    pf.CHARACTER.animatedCharacter = false;
    pf.CHARACTER.backgroundColor = 0;
    pf.CHARACTER.boldCharacter = false;
    pf.CHARACTER.capitalCharacter = false;
    pf.CHARACTER.doublestrikeCharacter = false;
    pf.CHARACTER.embossCharacter = false;
    pf.CHARACTER.engraveCharacter = false;
    pf.CHARACTER.expandCharacter = 0;
    pf.CHARACTER.fontNumber = 0;
    pf.CHARACTER.fontSize = 24;
    pf.CHARACTER.foregroundColor = 0;
    pf.CHARACTER.italicCharacter = false;
    pf.CHARACTER.kerningCharacter = 0;
    pf.CHARACTER.outlineCharacter = false;
    pf.CHARACTER.scaleCharacter = 100;
    pf.CHARACTER.shadowCharacter = false;
    pf.CHARACTER.smallcapitalCharacter = false;
    pf.CHARACTER.strikeCharacter = false;
    pf.CHARACTER.subscriptCharacter = false;
    pf.CHARACTER.superscriptCharacter = false;
    pf.CHARACTER.underlineCharacter = 0;
    pf.NUMS.numsChar = char(0x95);
    pf.NUMS.numsLevel = 11;
    pf.NUMS.numsSpace = 360;
    pf.SHADING.shadingBkColor = 0;
    pf.SHADING.shadingFillColor = 0;
    pf.SHADING.shadingIntensity = 0;
    pf.SHADING.shadingType = RTF_PARAGRAPHSHADINGTYPE_FILL;
    pf.TABS.tabKind = RTF_PARAGRAPHTABKIND_NONE;
    pf.TABS.tabLead = RTF_PARAGRAPHTABLEAD_NONE;
    pf.TABS.tabPosition = 0;
    set_paragraphformat(&pf);

    // Set default RTF table row formatting properties
    RTF_TABLEROW_FORMAT rf = {RTF_ROWTEXTALIGN_LEFT, 0, 0, 0, 0, 0, 0};
    set_tablerowformat(&rf);

    // Set default RTF table cell formatting properties
    RTF_TABLECELL_FORMAT cf = {RTF_CELLTEXTALIGN_CENTER, 0, 0, 0, 0, RTF_CELLTEXTDIRECTION_LRTB, false};
    cf.SHADING.shadingBkColor = 0;
    cf.SHADING.shadingFillColor = 0;
    cf.SHADING.shadingIntensity = 0;
    cf.SHADING.shadingType = RTF_PARAGRAPHSHADINGTYPE_FILL;
    cf.borderBottom.border = false;
    cf.borderBottom.BORDERS.borderColor = 0;
    cf.borderBottom.BORDERS.borderKind = RTF_PARAGRAPHBORDERKIND_NONE;
    cf.borderBottom.BORDERS.borderSpace = 0;
    cf.borderBottom.BORDERS.borderType = RTF_PARAGRAPHBORDERTYPE_STHICK;
    cf.borderBottom.BORDERS.borderWidth = 5;
    cf.borderLeft.border = false;
    cf.borderLeft.BORDERS.borderColor = 0;
    cf.borderLeft.BORDERS.borderKind = RTF_PARAGRAPHBORDERKIND_NONE;
    cf.borderLeft.BORDERS.borderSpace = 0;
    cf.borderLeft.BORDERS.borderType = RTF_PARAGRAPHBORDERTYPE_STHICK;
    cf.borderLeft.BORDERS.borderWidth = 5;
    cf.borderRight.border = false;
    cf.borderRight.BORDERS.borderColor = 0;
    cf.borderRight.BORDERS.borderKind = RTF_PARAGRAPHBORDERKIND_NONE;
    cf.borderRight.BORDERS.borderSpace = 0;
    cf.borderRight.BORDERS.borderType = RTF_PARAGRAPHBORDERTYPE_STHICK;
    cf.borderRight.BORDERS.borderWidth = 5;
    cf.borderTop.border = false;
    cf.borderTop.BORDERS.borderColor = 0;
    cf.borderTop.BORDERS.borderKind = RTF_PARAGRAPHBORDERKIND_NONE;
    cf.borderTop.BORDERS.borderSpace = 0;
    cf.borderTop.BORDERS.borderType = RTF_PARAGRAPHBORDERTYPE_STHICK;
    cf.borderTop.BORDERS.borderWidth = 5;
    set_tablecellformat(&cf);
}


// Sets new RTF document font table
void RtfWriter::set_fonttable( char* fonts )
{
    // Clear old font table
    _rtfFontTable =  "";

    // Set separator list
    char separator[] = ";";

    // Create new RTF document font table
    int font_number = 0;
    char font_table_entry[1024];
    char* token = strtok( fonts, separator );
    while ( token != NULL )
    {
        // Format font table entry
        sprintf( font_table_entry, "{\\f%d\\fnil\\fcharset0\\cpg1252 %s}", font_number, token );
        _rtfFontTable += font_table_entry;
        //strcat( _rtfFontTable, font_table_entry );

        // Get next font
        token = strtok( NULL, separator );
        font_number++;
    }
}


// Sets new RTF document color table
void RtfWriter::set_colortable(char* colors)
{
    // Clear old color table
    _rtfColorTable.clear();
    //strcpy( _rtfColorTable, "" );

    // Set separator list
    char separator[] = ";";

    // Create new RTF document color table
    int color_number = 0;
    char color_table_entry[1024];
    char* token = strtok( colors, separator );
    while ( token != NULL )
    {
        // Red
        sprintf( color_table_entry, "\\red%s", token );
        _rtfColorTable += color_table_entry;
        //strcat( _rtfColorTable, color_table_entry );

        // Green
        token = strtok( NULL, separator );
        if ( token != NULL )
        {
            sprintf( color_table_entry, "\\green%s", token );
            _rtfColorTable += color_table_entry;
            //strcat( _rtfColorTable, color_table_entry );
        }

        // Blue
        token = strtok( NULL, separator );
        if ( token != NULL )
        {
            sprintf( color_table_entry, "\\blue%s;", token );
            _rtfColorTable += color_table_entry;
            //strcat( _rtfColorTable, color_table_entry );
        }

        // Get next color
        token = strtok( NULL, separator );
        color_number++;
    }
}


// Sets RTF document formatting properties
void RtfWriter::set_documentformat(RTF_DOCUMENT_FORMAT* df)
{
    // Set new RTF document formatting properties
    memcpy( &_rtfDocFormat, df, sizeof(RTF_DOCUMENT_FORMAT) );
}


// Writes RTF document formatting properties
bool RtfWriter::write_documentformat()
{
    // Set error flag
    bool result = true;

    // RTF document text
    char rtfText[1024];
    strcpy( rtfText, "" );

    sprintf( rtfText, "\\viewkind%d\\viewscale%d\\paperw%d\\paperh%d\\margl%d\\margr%d\\margt%d\\margb%d\\gutter%d",
        _rtfDocFormat.viewKind, _rtfDocFormat.viewScale, _rtfDocFormat.paperWidth, _rtfDocFormat.paperHeight,
        _rtfDocFormat.marginLeft, _rtfDocFormat.marginRight, _rtfDocFormat.marginTop, _rtfDocFormat.marginBottom, _rtfDocFormat.gutterWidth );

    if ( _rtfDocFormat.facingPages )
        strcat( rtfText, "\\facingp" );
    if ( _rtfDocFormat.readOnly )
        strcat( rtfText, "\\annotprot" );

    // Writes RTF document formatting properties
    if ( fwrite( rtfText, 1, strlen(rtfText), _rtfFile ) < strlen(rtfText) )
        result = false;

    // Return error flag
    return result;
}


// Sets RTF section formatting properties
void RtfWriter::set_sectionformat(RTF_SECTION_FORMAT* sf)
{
    // Set new RTF section formatting properties
    memcpy( &_rtfSecFormat, sf, sizeof(RTF_SECTION_FORMAT) );
}


// Writes RTF section formatting properties
bool RtfWriter::write_sectionformat()
{
    // Set error flag
    bool result = true;

    // RTF document text
    char rtfText[1024];
    strcpy( rtfText, "" );

    // Format new section
    char text[1024]="", pgn[100]="";
    if ( _rtfSecFormat.newSection )
        strcat( text, "\\sect" );
    if ( _rtfSecFormat.defaultSection )
        strcat( text, "\\sectd" );
    if ( _rtfSecFormat.showPageNumber )
    {
        sprintf( pgn, "\\pgnx%d\\pgny%d", _rtfSecFormat.pageNumberOffsetX, _rtfSecFormat.pageNumberOffsetY );
        strcat( text, pgn );
    }

    // Format section break
    char sbr[100] = "";
    switch (_rtfSecFormat.sectionBreak)
    {
        // Continuous break
        case RTF_SECTIONBREAK_CONTINUOUS:
            strcat( sbr, "\\sbknone" );
            break;

        // Column break
        case RTF_SECTIONBREAK_COLUMN:
            strcat( sbr, "\\sbkcol" );
            break;

        // Page break
        case RTF_SECTIONBREAK_PAGE:
            strcat( sbr, "\\sbkpage" );
            break;

        // Even-page break
        case RTF_SECTIONBREAK_EVENPAGE:
            strcat( sbr, "\\sbkeven" );
            break;

        // Odd-page break
        case RTF_SECTIONBREAK_ODDPAGE:
            strcat( sbr, "\\sbkodd" );
            break;
    }

    // Format section columns
    char cols[100] = "";
    if ( _rtfSecFormat.cols == true )
    {
        // Format columns
        sprintf( cols, "\\cols%d\\colsx%d", _rtfSecFormat.colsNumber, _rtfSecFormat.colsDistance );

        if ( _rtfSecFormat.colsLineBetween )
            strcat( cols, "\\linebetcol" );
    }

    sprintf( rtfText, "\n%s%s%s\\pgwsxn%d\\pghsxn%d\\marglsxn%d\\margrsxn%d\\margtsxn%d\\margbsxn%d\\guttersxn%d\\headery%d\\footery%d",
        text, sbr, cols, _rtfSecFormat.pageWidth, _rtfSecFormat.pageHeight, _rtfSecFormat.pageMarginLeft, _rtfSecFormat.pageMarginRight,
        _rtfSecFormat.pageMarginTop, _rtfSecFormat.pageMarginBottom, _rtfSecFormat.pageGutterWidth, _rtfSecFormat.pageHeaderOffset, _rtfSecFormat.pageFooterOffset );

    // Writes RTF section formatting properties
    if ( fwrite( rtfText, 1, strlen(rtfText), _rtfFile ) < strlen(rtfText) )
        result = false;

    // Return error flag
    return result;
}


// Starts new RTF section
int RtfWriter::start_section()
{
    // Set error flag
    int error = RTF_SUCCESS;

    // Set new section flag
    _rtfSecFormat.newSection = true;

    // Starts new RTF section
    if( !RtfWriter::write_sectionformat() )
        error = RTF_SECTIONFORMAT_ERROR;

    // Return error flag
    return error;
}


// Sets RTF paragraph formatting properties
void RtfWriter::set_paragraphformat(RTF_PARAGRAPH_FORMAT* pf)
{
    // Set new RTF paragraph formatting properties
    memcpy( &_rtfParFormat, pf, sizeof(RTF_PARAGRAPH_FORMAT) );
}


// Writes RTF paragraph formatting properties
bool RtfWriter::write_paragraphformat()
{
    // Set error flag
    bool result = true;

    // RTF document text
    char rtfText[4096];
    strcpy( rtfText, "" );

    // Format new paragraph
    char text[1024] = "";
    if ( _rtfParFormat.newParagraph )
        strcat( text, "\\par" );
    if ( _rtfParFormat.defaultParagraph )
        strcat( text, "\\pard" );
    if ( _rtfParFormat.tableText == false )
        strcat( text, "\\plain" );
    else
        strcat( text, "\\intbl" );

    switch (_rtfParFormat.paragraphBreak)
    {
        // No break
        case RTF_PARAGRAPHBREAK_NONE:
            break;

        // Page break;
        case RTF_PARAGRAPHBREAK_PAGE:
            strcat( text, "\\page" );
            break;

        // Column break;
        case RTF_PARAGRAPHBREAK_COLUMN:
            strcat( text, "\\column" );
            break;

        // Line break;
        case RTF_PARAGRAPHBREAK_LINE:
            strcat( text, "\\line" );
            break;
    }

    // Format aligment
    switch (_rtfParFormat.paragraphAligment)
    {
        // Left aligned paragraph
        case RTF_PARAGRAPHALIGN_LEFT:
            strcat( text, "\\ql" );
            break;

        // Center aligned paragraph
        case RTF_PARAGRAPHALIGN_CENTER:
            strcat( text, "\\qc" );
            break;

        // Right aligned paragraph
        case RTF_PARAGRAPHALIGN_RIGHT:
            strcat( text, "\\qr" );
            break;

        // Justified aligned paragraph
        case RTF_PARAGRAPHALIGN_JUSTIFY:
            strcat( text, "\\qj" );
            break;
    }

    // Format tabs
    if ( _rtfParFormat.paragraphTabs == true )
    {
        // Set tab kind
        switch ( _rtfParFormat.TABS.tabKind )
        {
            // No tab
            case RTF_PARAGRAPHTABKIND_NONE:
                break;

            // Centered tab
            case RTF_PARAGRAPHTABKIND_CENTER:
                strcat( text, "\\tqc" );
                break;

            // Flush-right tab
            case RTF_PARAGRAPHTABKIND_RIGHT:
                strcat( text, "\\tqr" );
                break;

            // Decimal tab
            case RTF_PARAGRAPHTABKIND_DECIMAL:
                strcat( text, "\\tqdec" );
                break;
        }

        // Set tab leader
        switch ( _rtfParFormat.TABS.tabLead )
        {
            // No lead
            case RTF_PARAGRAPHTABLEAD_NONE:
                break;

            // Leader dots
            case RTF_PARAGRAPHTABLEAD_DOT:
                strcat( text, "\\tldot" );
                break;

            // Leader middle dots
            case RTF_PARAGRAPHTABLEAD_MDOT:
                strcat( text, "\\tlmdot" );
                break;

            // Leader hyphens
            case RTF_PARAGRAPHTABLEAD_HYPH:
                strcat( text, "\\tlhyph" );
                break;

            // Leader underline
            case RTF_PARAGRAPHTABLEAD_UNDERLINE:
                strcat( text, "\\tlul" );
                break;

            // Leader thick line
            case RTF_PARAGRAPHTABLEAD_THICKLINE:
                strcat( text, "\\tlth" );
                break;

            // Leader equal sign
            case RTF_PARAGRAPHTABLEAD_EQUAL:
                strcat( text, "\\tleq" );
                break;
        }

        // Set tab position
        char tb[10];
        sprintf( tb, "\\tx%d", _rtfParFormat.TABS.tabPosition );
        strcat( text, tb );
    }

    // Format bullets and numbering
    if ( _rtfParFormat.paragraphNums == true )
    {
        char nums[1024];
        sprintf( nums, "{\\*\\pn\\pnlvl%d\\pnsp%d\\pntxtb %c}", _rtfParFormat.NUMS.numsLevel, _rtfParFormat.NUMS.numsSpace, _rtfParFormat.NUMS.numsChar );
        strcat( text, nums );
    }

    // Format paragraph borders
    if ( _rtfParFormat.paragraphBorders == true )
    {
        char border[1024] = "";

        // Format paragraph border kind
        switch (_rtfParFormat.BORDERS.borderKind)
        {
            // No border
            case RTF_PARAGRAPHBORDERKIND_NONE:
                break;

            // Border top
            case RTF_PARAGRAPHBORDERKIND_TOP:
                strcat( border, "\\brdrt" );
                break;

            // Border bottom
            case RTF_PARAGRAPHBORDERKIND_BOTTOM:
                strcat( border, "\\brdrb" );
                break;

            // Border left
            case RTF_PARAGRAPHBORDERKIND_LEFT:
                strcat( border, "\\brdrl" );
                break;

            // Border right
            case RTF_PARAGRAPHBORDERKIND_RIGHT:
                strcat( border, "\\brdrr" );
                break;

            // Border box
            case RTF_PARAGRAPHBORDERKIND_BOX:
                strcat( border, "\\box" );
                break;
        }

        // Format paragraph border type
        char *br = RtfWriter::get_bordername(_rtfParFormat.BORDERS.borderType);
        strcat( border, br );

        // Set paragraph border width
        char brd[100];
        sprintf( brd, "\\brdrw%d\\brsp%d", _rtfParFormat.BORDERS.borderWidth, _rtfParFormat.BORDERS.borderSpace );
        strcat( border, brd );
        strcat( text, border );

        // Set paragraph border color
        char brdcol[100];
        sprintf( brdcol, "\\brdrcf%d", _rtfParFormat.BORDERS.borderColor );
        strcat( text, brdcol );
    }

    // Format paragraph shading
    if ( _rtfParFormat.paragraphShading == true )
    {
        char shading[100];
        sprintf( shading, "\\shading%d", _rtfParFormat.SHADING.shadingIntensity );

        // Format paragraph shading
        char* sh = RtfWriter::get_shadingname( _rtfParFormat.SHADING.shadingType, false );
        strcat( text, sh );

        // Set paragraph shading color
        char shcol[100];
        sprintf( shcol, "\\cfpat%d\\cbpat%d", _rtfParFormat.SHADING.shadingFillColor, _rtfParFormat.SHADING.shadingBkColor );
        strcat( text, shcol );
    }

    // Format paragraph font
    char font[1024] = "";
    sprintf( font, "\\animtext%d\\expndtw%d\\kerning%d\\charscalex%d\\f%d\\fs%d\\cf%d", _rtfParFormat.CHARACTER.animatedCharacter,
        _rtfParFormat.CHARACTER.expandCharacter, _rtfParFormat.CHARACTER.kerningCharacter, _rtfParFormat.CHARACTER.scaleCharacter,
        _rtfParFormat.CHARACTER.fontNumber, _rtfParFormat.CHARACTER.fontSize, _rtfParFormat.CHARACTER.foregroundColor );
    if ( _rtfParFormat.CHARACTER.boldCharacter )
        strcat( font, "\\b" );
    else
        strcat( font, "\\b0" );
    if ( _rtfParFormat.CHARACTER.capitalCharacter )
        strcat( font, "\\caps" );
    else
        strcat( font, "\\caps0" );
    if ( _rtfParFormat.CHARACTER.doublestrikeCharacter )
        strcat( font, "\\striked1" );
    else
        strcat( font, "\\striked0" );
    if ( _rtfParFormat.CHARACTER.embossCharacter )
        strcat( font, "\\embo" );
    if ( _rtfParFormat.CHARACTER.engraveCharacter )
        strcat( font, "\\impr" );
    if ( _rtfParFormat.CHARACTER.italicCharacter )
        strcat( font, "\\i" );
    else
        strcat( font, "\\i0" );
    if ( _rtfParFormat.CHARACTER.outlineCharacter )
        strcat( font, "\\outl" );
    else
        strcat( font, "\\outl0" );
    if ( _rtfParFormat.CHARACTER.shadowCharacter )
        strcat( font, "\\shad" );
    else
        strcat( font, "\\shad0" );
    if ( _rtfParFormat.CHARACTER.smallcapitalCharacter )
        strcat( font, "\\scaps" );
    else
        strcat( font, "\\scaps0" );
    if ( _rtfParFormat.CHARACTER.strikeCharacter )
        strcat( font, "\\strike" );
    else
        strcat( font, "\\strike0" );
    if ( _rtfParFormat.CHARACTER.subscriptCharacter )
        strcat( font, "\\sub" );
    if ( _rtfParFormat.CHARACTER.superscriptCharacter )
        strcat( font, "\\super" );

    switch (_rtfParFormat.CHARACTER.underlineCharacter)
    {
        // None underline
        case 0:
            strcat( font, "\\ulnone" );
            break;

        // Continuous underline
        case 1:
            strcat( font, "\\ul" );
            break;

        // Dotted underline
        case 2:
            strcat( font, "\\uld" );
            break;

        // Dashed underline
        case 3:
            strcat( font, "\\uldash" );
            break;

        // Dash-dotted underline
        case 4:
            strcat( font, "\\uldashd" );
            break;

        // Dash-dot-dotted underline
        case 5:
            strcat( font, "\\uldashdd" );
            break;

        // Double underline
        case 6:
            strcat( font, "\\uldb" );
            break;

        // Heavy wave underline
        case 7:
            strcat( font, "\\ulhwave" );
            break;

        // Long dashed underline
        case 8:
            strcat( font, "\\ulldash" );
            break;

        // Thick underline
        case 9:
            strcat( font, "\\ulth" );
            break;

        // Thick dotted underline
        case 10:
            strcat( font, "\\ulthd" );
            break;

        // Thick dashed underline
        case 11:
            strcat( font, "\\ulthdash" );
            break;

        // Thick dash-dotted underline
        case 12:
            strcat( font, "\\ulthdashd" );
            break;

        // Thick dash-dot-dotted underline
        case 13:
            strcat( font, "\\ulthdashdd" );
            break;

        // Thick long dashed underline
        case 14:
            strcat( font, "\\ulthldash" );
            break;

        // Double wave underline
        case 15:
            strcat( font, "\\ululdbwave" );
            break;

        // Word underline
        case 16:
            strcat( font, "\\ulw" );
            break;

        // Wave underline
        case 17:
            strcat( font, "\\ulwave" );
            break;
    }

    char txt[20] = "";
    // Set paragraph tabbed text
    if ( _rtfParFormat.tabbedText == false )
    {
        sprintf( rtfText, "\n%s\\fi%d\\li%d\\ri%d\\sb%d\\sa%d\\sl%d%s %s", text,
            _rtfParFormat.firstLineIndent, _rtfParFormat.leftIndent, _rtfParFormat.rightIndent, _rtfParFormat.spaceBefore,
            _rtfParFormat.spaceAfter, _rtfParFormat.lineSpacing, font, _rtfParFormat.paragraphText );
    }
    else
        sprintf( rtfText, "\\tab %s", _rtfParFormat.paragraphText );

    // Writes RTF paragraph formatting properties
    if ( fwrite( rtfText, 1, strlen(rtfText), _rtfFile ) < strlen(rtfText) )
        result = false;

    // Return error flag
    return result;
}


// Starts new RTF paragraph
int RtfWriter::start_paragraph(const char* text, bool newPar)
{
    // Set error flag
    int error = RTF_SUCCESS;

    // Copy paragraph text
    _rtfParFormat.paragraphText = new char[strlen(text)];
    strcpy( _rtfParFormat.paragraphText, text );

    // Set new paragraph
    _rtfParFormat.newParagraph = newPar;

    // Starts new RTF paragraph
    if( !RtfWriter::write_paragraphformat() )
        error = RTF_PARAGRAPHFORMAT_ERROR;

    // Return error flag
    return error;
}


// Gets RTF document formatting properties
RTF_DOCUMENT_FORMAT* RtfWriter::get_documentformat()
{
    // Get current RTF document formatting properties
    return &_rtfDocFormat;
}

// Gets RTF section formatting properties
RTF_SECTION_FORMAT* RtfWriter::get_sectionformat()
{
    // Get current RTF section formatting properties
    return &_rtfSecFormat;
}


// Gets RTF paragraph formatting properties
RTF_PARAGRAPH_FORMAT* RtfWriter::get_paragraphformat()
{
    // Get current RTF paragraph formatting properties
    return &_rtfParFormat;
}


// Loads image from file
int RtfWriter::load_image(char* image, int width, int height)
{
    return -1;
}


// Converts binary data to hex
char* RtfWriter::bin_hex_convert(unsigned char* binary, int size)
{
    char* result = new char[2*size];

    char part1, part2;
    for ( int i=0; i<size; i++ )
    {
        part1 = binary[i] / 16;
        if ( part1 < 10 )
            part1 += 48;
        else
        {
            if ( part1 == 10 )
                part1 = 'a';
            if ( part1 == 11 )
                part1 = 'b';
            if ( part1 == 12 )
                part1 = 'c';
            if ( part1 == 13 )
                part1 = 'd';
            if ( part1 == 14 )
                part1 = 'e';
            if ( part1 == 15 )
                part1 = 'f';
        }

        part2 = binary[i] % 16;
        if ( part2 < 10 )
            part2 += 48;
        else
        {
            if ( part2 == 10 )
                part2 = 'a';
            if ( part2 == 11 )
                part2 = 'b';
            if ( part2 == 12 )
                part2 = 'c';
            if ( part2 == 13 )
                part2 = 'd';
            if ( part2 == 14 )
                part2 = 'e';
            if ( part2 == 15 )
                part2 = 'f';
        }

        result[2*i] = part1;
        result[2*i+1] = part2;
    }

    strcat( result, "\0" );

    return result;
}


// Starts new RTF table row
int RtfWriter::start_tablerow()
{
    // Set error flag
    int error = RTF_SUCCESS;

    char tblrw[1024]="";
    // Format table row aligment
    switch (_rtfRowFormat.rowAligment)
    {
        // Left align
        case RTF_ROWTEXTALIGN_LEFT:
            strcat( tblrw, "\\trql" );
            break;

        // Center align
        case RTF_ROWTEXTALIGN_CENTER:
            strcat( tblrw, "\\trqc" );
            break;

        // Right align
        case RTF_ROWTEXTALIGN_RIGHT:
            strcat( tblrw, "\\trqr" );
            break;
    }

    // Writes RTF table data
    char rtfText[1024]="";
    sprintf( rtfText, "\n\\trowd\\trgaph115%s\\trleft%d\\trrh%d\\trpaddb%d\\trpaddfb3\\trpaddl%d\\trpaddfl3\\trpaddr%d\\trpaddfr3\\trpaddt%d\\trpaddft3",
        tblrw, _rtfRowFormat.rowLeftMargin, _rtfRowFormat.rowHeight, _rtfRowFormat.marginTop, _rtfRowFormat.marginBottom, _rtfRowFormat.marginLeft, _rtfRowFormat.marginRight );
    if ( fwrite( rtfText, 1, strlen(rtfText), _rtfFile ) < strlen(rtfText) )
        error = RTF_TABLE_ERROR;

    // Return error flag
    return error;
}


// Ends RTF table row
int RtfWriter::end_tablerow()
{
    // Set error flag
    int error = RTF_SUCCESS;

    // Writes RTF table data
    char rtfText[1024];
    sprintf( rtfText, "\n\\trgaph115\\row\\pard" );
    if ( fwrite( rtfText, 1, strlen(rtfText), _rtfFile ) < strlen(rtfText) )
        error = RTF_TABLE_ERROR;

    // Return error flag
    return error;
}


// Starts new RTF table cell
int RtfWriter::start_tablecell(int rightMargin)
{
    // Set error flag
    int error = RTF_SUCCESS;

    char tblcla[20]="";
    // Format table cell text aligment
    switch (_rtfCellFormat.textVerticalAligment)
    {
        // Top align
        case RTF_CELLTEXTALIGN_TOP:
            strcpy( tblcla, "\\clvertalt" );
            break;

        // Center align
        case RTF_CELLTEXTALIGN_CENTER:
            strcpy( tblcla, "\\clvertalc" );
            break;

        // Bottom align
        case RTF_CELLTEXTALIGN_BOTTOM:
            strcpy( tblcla, "\\clvertalb" );
            break;
    }

    char tblcld[20];
    // Format table cell text direction
    switch (_rtfCellFormat.textDirection)
    {
        // Left to right, top to bottom
        case RTF_CELLTEXTDIRECTION_LRTB:
            strcpy( tblcld, "\\cltxlrtb" );
            break;

        // Right to left, top to bottom
        case RTF_CELLTEXTDIRECTION_RLTB:
            strcpy( tblcld, "\\cltxtbrl" );
            break;

        // Left to right, bottom to top
        case RTF_CELLTEXTDIRECTION_LRBT:
            strcpy( tblcld, "\\cltxbtlr" );
            break;

        // Left to right, top to bottom, vertical
        case RTF_CELLTEXTDIRECTION_LRTBV:
            strcpy( tblcld, "\\cltxlrtbv" );
            break;

        // Right to left, top to bottom, vertical
        case RTF_CELLTEXTDIRECTION_RLTBV:
            strcpy( tblcld, "\\cltxtbrlv" );
            break;
    }

    char tbclbrb[1024]="", tbclbrl[1024]="", tbclbrr[1024]="", tbclbrt[1024]="";
    // Format table cell border
    if ( _rtfCellFormat.borderBottom.border == true )
    {
        // Bottom cell border
        char tbclbt[20];
        strcpy( tbclbt, "\\clbrdrb" );

        char* border = RtfWriter::get_bordername(_rtfCellFormat.borderBottom.BORDERS.borderType);

        sprintf( tbclbrb, "%s%s\\brdrw%d\\brsp%d\\brdrcf%d", tbclbt, border, _rtfCellFormat.borderBottom.BORDERS.borderWidth,
            _rtfCellFormat.borderBottom.BORDERS.borderSpace, _rtfCellFormat.borderBottom.BORDERS.borderColor );
    }
    if ( _rtfCellFormat.borderLeft.border == true )
    {
        // Left cell border
        char tbclbt[20]="";
        strcpy( tbclbt, "\\clbrdrl" );

        char* border = RtfWriter::get_bordername(_rtfCellFormat.borderLeft.BORDERS.borderType);

        sprintf( tbclbrl, "%s%s\\brdrw%d\\brsp%d\\brdrcf%d", tbclbt, border, _rtfCellFormat.borderLeft.BORDERS.borderWidth,
        _rtfCellFormat.borderLeft.BORDERS.borderSpace, _rtfCellFormat.borderLeft.BORDERS.borderColor );
    }
    if ( _rtfCellFormat.borderRight.border == true )
    {
        // Right cell border
        char tbclbt[20];
        strcpy( tbclbt, "\\clbrdrr" );

        char* border = RtfWriter::get_bordername(_rtfCellFormat.borderRight.BORDERS.borderType);

        sprintf( tbclbrr, "%s%s\\brdrw%d\\brsp%d\\brdrcf%d", tbclbt, border, _rtfCellFormat.borderRight.BORDERS.borderWidth,
        _rtfCellFormat.borderRight.BORDERS.borderSpace, _rtfCellFormat.borderRight.BORDERS.borderColor );
    }
    if ( _rtfCellFormat.borderTop.border == true )
    {
        // Top cell border
        char tbclbt[20];
        strcpy( tbclbt, "\\clbrdrt" );

        char* border = RtfWriter::get_bordername(_rtfCellFormat.borderTop.BORDERS.borderType);

        sprintf( tbclbrt, "%s%s\\brdrw%d\\brsp%d\\brdrcf%d", tbclbt, border, _rtfCellFormat.borderTop.BORDERS.borderWidth,
        _rtfCellFormat.borderTop.BORDERS.borderSpace, _rtfCellFormat.borderTop.BORDERS.borderColor );
    }

    // Format table cell shading
    char shading[100] = "";
    if ( _rtfCellFormat.cellShading == true )
    {
        char* sh = RtfWriter::get_shadingname( _rtfCellFormat.SHADING.shadingType, true );

        // Set paragraph shading color
        sprintf( shading, "%s\\clshdgn%d\\clcfpat%d\\clcbpat%d", sh, _rtfCellFormat.SHADING.shadingIntensity, _rtfCellFormat.SHADING.shadingFillColor, _rtfCellFormat.SHADING.shadingBkColor );
    }

    // Writes RTF table data
    char rtfText[1024];
    sprintf( rtfText, "\n\\tcelld%s%s%s%s%s%s%s\\cellx%d", tblcla, tblcld, tbclbrb, tbclbrl, tbclbrr, tbclbrt, shading, rightMargin );
    if ( fwrite( rtfText, 1, strlen(rtfText), _rtfFile ) < strlen(rtfText) )
        error = RTF_TABLE_ERROR;

    // Return error flag
    return error;
}


// Ends RTF table cell
int RtfWriter::end_tablecell()
{
    // Set error flag
    int error = RTF_SUCCESS;

    // Writes RTF table data
    char rtfText[1024];
    strcpy( rtfText, "\n\\cell " );
    if ( fwrite( rtfText, 1, strlen(rtfText), _rtfFile ) < strlen(rtfText) )
        error = RTF_TABLE_ERROR;

    // Return error flag
    return error;
}


// Gets RTF table row formatting properties
RTF_TABLEROW_FORMAT* RtfWriter::get_tablerowformat()
{
    // Get current RTF table row formatting properties
    return &_rtfRowFormat;
}


// Sets RTF table row formatting properties
void RtfWriter::set_tablerowformat(RTF_TABLEROW_FORMAT* rf)
{
    // Set new RTF table row formatting properties
    memcpy( &_rtfRowFormat, rf, sizeof(RTF_TABLEROW_FORMAT) );
}


// Gets RTF table cell formatting properties
RTF_TABLECELL_FORMAT* RtfWriter::get_tablecellformat()
{
    // Get current RTF table cell formatting properties
    return &_rtfCellFormat;
}


// Sets RTF table cell formatting properties
void RtfWriter::set_tablecellformat(RTF_TABLECELL_FORMAT* cf)
{
    // Set new RTF table cell formatting properties
    memcpy( &_rtfCellFormat, cf, sizeof(RTF_TABLECELL_FORMAT) );
}


// Gets border name
char* RtfWriter::get_bordername(int border_type)
{
    char* border = new char[20];

    switch (border_type)
    {
        // Single-thickness border
        case RTF_PARAGRAPHBORDERTYPE_STHICK:
            strcpy( border, "\\brdrs" );
            break;

        // Double-thickness border
        case RTF_PARAGRAPHBORDERTYPE_DTHICK:
            strcpy( border, "\\brdrth" );
            break;

        // Shadowed border
        case RTF_PARAGRAPHBORDERTYPE_SHADOW:
            strcpy( border, "\\brdrsh" );
            break;

        // Double border
        case RTF_PARAGRAPHBORDERTYPE_DOUBLE:
            strcpy( border, "\\brdrdb" );
            break;

        // Dotted border
        case RTF_PARAGRAPHBORDERTYPE_DOT:
            strcpy( border, "\\brdrdot" );
            break;

        // Dashed border
        case RTF_PARAGRAPHBORDERTYPE_DASH:
            strcpy( border, "\\brdrdash" );
            break;

        // Hairline border
        case RTF_PARAGRAPHBORDERTYPE_HAIRLINE:
            strcpy( border, "\\brdrhair" );
            break;

        // Inset border
        case RTF_PARAGRAPHBORDERTYPE_INSET:
            strcpy( border, "\\brdrinset" );
            break;

        // Dashed border (small)
        case RTF_PARAGRAPHBORDERTYPE_SDASH:
            strcpy( border, "\\brdrdashsm" );
            break;

        // Dot-dashed border
        case RTF_PARAGRAPHBORDERTYPE_DOTDASH:
            strcpy( border, "\\brdrdashd" );
            break;

        // Dot-dot-dashed border
        case RTF_PARAGRAPHBORDERTYPE_DOTDOTDASH:
            strcpy( border, "\\brdrdashdd" );
            break;

        // Outset border
        case RTF_PARAGRAPHBORDERTYPE_OUTSET:
            strcpy( border, "\\brdroutset" );
            break;

        // Triple border
        case RTF_PARAGRAPHBORDERTYPE_TRIPLE:
            strcpy( border, "\\brdrtriple" );
            break;

        // Wavy border
        case RTF_PARAGRAPHBORDERTYPE_WAVY:
            strcpy( border, "\\brdrwavy" );
            break;

        // Double wavy border
        case RTF_PARAGRAPHBORDERTYPE_DWAVY:
            strcpy( border, "\\brdrwavydb" );
            break;

        // Striped border
        case RTF_PARAGRAPHBORDERTYPE_STRIPED:
            strcpy( border, "\\brdrdashdotstr" );
            break;

        // Embossed border
        case RTF_PARAGRAPHBORDERTYPE_EMBOSS:
            strcpy( border, "\\brdremboss" );
            break;

        // Engraved border
        case RTF_PARAGRAPHBORDERTYPE_ENGRAVE:
            strcpy( border, "\\brdrengrave" );
            break;
    }

    return border;
}


// Gets shading name
char* RtfWriter::get_shadingname(int shading_type, bool cell)
{
    char* shading = new char[20];

    if ( cell == false )
    {
        switch (shading_type)
        {
            // Fill shading
            case RTF_PARAGRAPHSHADINGTYPE_FILL:
                strcpy( shading, "" );
                break;

            // Horizontal background pattern
            case RTF_PARAGRAPHSHADINGTYPE_HORIZ:
                strcpy( shading, "\\bghoriz" );
                break;

            // Vertical background pattern
            case RTF_PARAGRAPHSHADINGTYPE_VERT:
                strcpy( shading, "\\bgvert" );
                break;

            // Forward diagonal background pattern
            case RTF_PARAGRAPHSHADINGTYPE_FDIAG:
                strcpy( shading, "\\bgfdiag" );
                break;

            // Backward diagonal background pattern
            case RTF_PARAGRAPHSHADINGTYPE_BDIAG:
                strcpy( shading, "\\bgbdiag" );
                break;

            // Cross background pattern
            case RTF_PARAGRAPHSHADINGTYPE_CROSS:
                strcpy( shading, "\\bgcross" );
                break;

            // Diagonal cross background pattern
            case RTF_PARAGRAPHSHADINGTYPE_CROSSD:
                strcpy( shading, "\\bgdcross" );
                break;

            // Dark horizontal background pattern
            case RTF_PARAGRAPHSHADINGTYPE_DHORIZ:
                strcpy( shading, "\\bgdkhoriz" );
                break;

            // Dark vertical background pattern
            case RTF_PARAGRAPHSHADINGTYPE_DVERT:
                strcpy( shading, "\\bgdkvert" );
                break;

            // Dark forward diagonal background pattern
            case RTF_PARAGRAPHSHADINGTYPE_DFDIAG:
                strcpy( shading, "\\bgdkfdiag" );
                break;

            // Dark backward diagonal background pattern
            case RTF_PARAGRAPHSHADINGTYPE_DBDIAG:
                strcpy( shading, "\\bgdkbdiag" );
                break;

            // Dark cross background pattern
            case RTF_PARAGRAPHSHADINGTYPE_DCROSS:
                strcpy( shading, "\\bgdkcross" );
                break;

            // Dark diagonal cross background pattern
            case RTF_PARAGRAPHSHADINGTYPE_DCROSSD:
                strcpy( shading, "\\bgdkdcross" );
                break;
        }
    }
    else
    {
        switch (shading_type)
        {
            // Fill shading
            case RTF_CELLSHADINGTYPE_FILL:
                strcpy( shading, "" );
                break;

            // Horizontal background pattern
            case RTF_CELLSHADINGTYPE_HORIZ:
                strcpy( shading, "\\clbghoriz" );
                break;

            // Vertical background pattern
            case RTF_CELLSHADINGTYPE_VERT:
                strcpy( shading, "\\clbgvert" );
                break;

            // Forward diagonal background pattern
            case RTF_CELLSHADINGTYPE_FDIAG:
                strcpy( shading, "\\clbgfdiag" );
                break;

            // Backward diagonal background pattern
            case RTF_CELLSHADINGTYPE_BDIAG:
                strcpy( shading, "\\clbgbdiag" );
                break;

            // Cross background pattern
            case RTF_CELLSHADINGTYPE_CROSS:
                strcpy( shading, "\\clbgcross" );
                break;

            // Diagonal cross background pattern
            case RTF_CELLSHADINGTYPE_CROSSD:
                strcpy( shading, "\\clbgdcross" );
                break;

            // Dark horizontal background pattern
            case RTF_CELLSHADINGTYPE_DHORIZ:
                strcpy( shading, "\\clbgdkhoriz" );
                break;

            // Dark vertical background pattern
            case RTF_CELLSHADINGTYPE_DVERT:
                strcpy( shading, "\\clbgdkvert" );
                break;

            // Dark forward diagonal background pattern
            case RTF_CELLSHADINGTYPE_DFDIAG:
                strcpy( shading, "\\clbgdkfdiag" );
                break;

            // Dark backward diagonal background pattern
            case RTF_CELLSHADINGTYPE_DBDIAG:
                strcpy( shading, "\\clbgdkbdiag" );
                break;

            // Dark cross background pattern
            case RTF_CELLSHADINGTYPE_DCROSS:
                strcpy( shading, "\\clbgdkcross" );
                break;

            // Dark diagonal cross background pattern
            case RTF_CELLSHADINGTYPE_DCROSSD:
                strcpy( shading, "\\clbgdkdcross" );
                break;
        }
    }

    return shading;
}


std::string         RtfWriter::encodeWString(const std::wstring& str)
{
    std::ostringstream sstr;
    for (size_t i = 0; i < str.length(); i++)
    {
        if(str[i] <= 0x7f )
            sstr  << (char) str[i];
        else 
            sstr<<"\\u" << str[i] << "?";//\uN and append the ansi representation of this char
    }
    return sstr.str();
}
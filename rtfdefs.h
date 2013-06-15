#pragma once

// RTF library error codes
#define RTF_OPEN_ERROR				0x0001			// Could not create RTF file
#define RTF_CLOSE_ERROR				0x0002			// Could not close RTF file
#define RTF_HEADER_ERROR			0x0003			// Could not write header part to RTF file
#define RTF_DOCUMENTFORMAT_ERROR	0x0004			// Could not write document formatting properties to RTF file
#define RTF_SECTIONFORMAT_ERROR		0x0005			// Could not write section formatting properties to RTF file
#define RTF_PARAGRAPHFORMAT_ERROR	0x0006			// Could not write paragraph formatting properties to RTF file
#define RTF_IMAGE_ERROR				0x0007			// Could not write image to RTF file
#define RTF_TABLE_ERROR				0x0008			// Could not write table to RTF file
#define RTF_SUCCESS					0x1000			// No error

// Paragraph break defs
#define RTF_PARAGRAPHBREAK_NONE				0
#define RTF_PARAGRAPHBREAK_PAGE				1
#define RTF_PARAGRAPHBREAK_COLUMN			2
#define RTF_PARAGRAPHBREAK_LINE				3

// Paragraph align defs
#define RTF_PARAGRAPHALIGN_LEFT				0
#define RTF_PARAGRAPHALIGN_CENTER			1
#define RTF_PARAGRAPHALIGN_RIGHT			2
#define RTF_PARAGRAPHALIGN_JUSTIFY			3

// Paragraph tab kind defs
#define RTF_PARAGRAPHTABKIND_NONE			0
#define RTF_PARAGRAPHTABKIND_CENTER			1
#define RTF_PARAGRAPHTABKIND_RIGHT			2
#define RTF_PARAGRAPHTABKIND_DECIMAL		3

// Paragraph tab lead defs
#define RTF_PARAGRAPHTABLEAD_NONE			0
#define RTF_PARAGRAPHTABLEAD_DOT			1
#define RTF_PARAGRAPHTABLEAD_MDOT			2
#define RTF_PARAGRAPHTABLEAD_HYPH			3
#define RTF_PARAGRAPHTABLEAD_UNDERLINE		4
#define RTF_PARAGRAPHTABLEAD_THICKLINE		5
#define RTF_PARAGRAPHTABLEAD_EQUAL			6

// Paragraph border kind defs
#define RTF_PARAGRAPHBORDERKIND_NONE		0
#define RTF_PARAGRAPHBORDERKIND_TOP			1
#define RTF_PARAGRAPHBORDERKIND_BOTTOM		2
#define RTF_PARAGRAPHBORDERKIND_LEFT		3
#define RTF_PARAGRAPHBORDERKIND_RIGHT		4
#define RTF_PARAGRAPHBORDERKIND_BOX			5

// Paragraph border type defs
#define RTF_PARAGRAPHBORDERTYPE_STHICK		0
#define RTF_PARAGRAPHBORDERTYPE_DTHICK		1
#define RTF_PARAGRAPHBORDERTYPE_SHADOW		2
#define RTF_PARAGRAPHBORDERTYPE_DOUBLE		3
#define RTF_PARAGRAPHBORDERTYPE_DOT			4
#define RTF_PARAGRAPHBORDERTYPE_DASH		5
#define RTF_PARAGRAPHBORDERTYPE_HAIRLINE	6
#define RTF_PARAGRAPHBORDERTYPE_INSET		7
#define RTF_PARAGRAPHBORDERTYPE_SDASH		8
#define RTF_PARAGRAPHBORDERTYPE_DOTDASH		9
#define RTF_PARAGRAPHBORDERTYPE_DOTDOTDASH	10
#define RTF_PARAGRAPHBORDERTYPE_OUTSET		11
#define RTF_PARAGRAPHBORDERTYPE_TRIPLE		12
#define RTF_PARAGRAPHBORDERTYPE_WAVY		13
#define RTF_PARAGRAPHBORDERTYPE_DWAVY		14
#define RTF_PARAGRAPHBORDERTYPE_STRIPED		15
#define RTF_PARAGRAPHBORDERTYPE_EMBOSS		16
#define RTF_PARAGRAPHBORDERTYPE_ENGRAVE		17

// Paragraph shading type defs
#define RTF_PARAGRAPHSHADINGTYPE_FILL		0
#define RTF_PARAGRAPHSHADINGTYPE_HORIZ		1
#define RTF_PARAGRAPHSHADINGTYPE_VERT		2
#define RTF_PARAGRAPHSHADINGTYPE_FDIAG		3
#define RTF_PARAGRAPHSHADINGTYPE_BDIAG		4
#define RTF_PARAGRAPHSHADINGTYPE_CROSS		5
#define RTF_PARAGRAPHSHADINGTYPE_CROSSD		6
#define RTF_PARAGRAPHSHADINGTYPE_DHORIZ		7
#define RTF_PARAGRAPHSHADINGTYPE_DVERT		8
#define RTF_PARAGRAPHSHADINGTYPE_DFDIAG		9
#define RTF_PARAGRAPHSHADINGTYPE_DBDIAG		10
#define RTF_PARAGRAPHSHADINGTYPE_DCROSS		11
#define RTF_PARAGRAPHSHADINGTYPE_DCROSSD	12

// Section break defs
#define RTF_SECTIONBREAK_CONTINUOUS			0
#define RTF_SECTIONBREAK_COLUMN				1
#define RTF_SECTIONBREAK_PAGE				2
#define RTF_SECTIONBREAK_EVENPAGE			3
#define RTF_SECTIONBREAK_ODDPAGE			4

// Table row text align defs
#define RTF_ROWTEXTALIGN_LEFT				0
#define RTF_ROWTEXTALIGN_CENTER				1
#define RTF_ROWTEXTALIGN_RIGHT				2

// Table cell text vertical align defs
#define RTF_CELLTEXTALIGN_TOP				0
#define RTF_CELLTEXTALIGN_CENTER			1
#define RTF_CELLTEXTALIGN_BOTTOM			2

// Table cell text direction defs
#define RTF_CELLTEXTDIRECTION_LRTB			0
#define RTF_CELLTEXTDIRECTION_RLTB			1
#define RTF_CELLTEXTDIRECTION_LRBT			2
#define RTF_CELLTEXTDIRECTION_LRTBV			3
#define RTF_CELLTEXTDIRECTION_RLTBV			4

// Table cell shading type defs
#define RTF_CELLSHADINGTYPE_FILL			0
#define RTF_CELLSHADINGTYPE_HORIZ			1
#define RTF_CELLSHADINGTYPE_VERT			2
#define RTF_CELLSHADINGTYPE_FDIAG			3
#define RTF_CELLSHADINGTYPE_BDIAG			4
#define RTF_CELLSHADINGTYPE_CROSS			5
#define RTF_CELLSHADINGTYPE_CROSSD			6
#define RTF_CELLSHADINGTYPE_DHORIZ			7
#define RTF_CELLSHADINGTYPE_DVERT			8
#define RTF_CELLSHADINGTYPE_DFDIAG			9
#define RTF_CELLSHADINGTYPE_DBDIAG			10
#define RTF_CELLSHADINGTYPE_DCROSS			11
#define RTF_CELLSHADINGTYPE_DCROSSD			12

// Document view kind defs
#define RTF_DOCUMENTVIEWKIND_NONE			0
#define RTF_DOCUMENTVIEWKIND_PAGE			1
#define RTF_DOCUMENTVIEWKIND_OUTLINE		2
#define RTF_DOCUMENTVIEWKIND_MASTER			3
#define RTF_DOCUMENTVIEWKIND_NORMAL			4

// RTF document format structure
struct RTF_DOCUMENT_FORMAT
{
	int viewKind;							// Sets document view mode
	int viewScale;							// Sets document zoom level
	int paperWidth;							// Sets document paper width (the default is 12240)
	int paperHeight;						// Sets document paper height (the default is 15840)
	int marginLeft;							// Left margin in twips (the default is 1800)
	int marginRight;						// Right margin in twips (the default is 1800)
	int marginTop;							// Top margin in twips (the default is 1440)
	int marginBottom;						// Bottom margin in twips (the default is 1440)
	bool facingPages;						// Facing pages (activates odd/even headers and gutters)
	int gutterWidth;						// Gutter width in twips (the default is 0)
	bool readOnly;							// User can't edit document
};



// RTF section format structure
struct RTF_SECTION_FORMAT
{
	int sectionBreak;						// Sets section break type
	bool newSection;						// New section
	bool defaultSection;					// Default section formatting
	int pageWidth;							// Sets new page width in twips
	int pageHeight;							// Sets new page height in twips
	int pageMarginLeft;						// Sets new page left margin in twips
	int pageMarginRight;					// Sets new page right margin in twips
	int pageMarginTop;						// Sets new page top margin in twips
	int pageMarginBottom;					// Sets new page bottom margin in twips
	int pageGutterWidth;					// Sets new page gutter width in twips
	int pageHeaderOffset;					// Sets page header offset in twips (the default is 720)
	int pageFooterOffset;					// Sets page footer offset in twips (the default is 720)
	bool showPageNumber;					// Show page number
	int pageNumberOffsetX;					// Sets page number right offset
	int pageNumberOffsetY;					// Sets page number top offset
	bool cols;								// Sets column section format
	int colsNumber;							// Sets number of columns in section
	int colsDistance;						// Sets distance between columns in twips
	bool colsLineBetween;					// Sets line between columns
};



// RTF tab format structure
struct RTF_TABS_FORMAT
{
	int tabPosition;						// Sets tab position in twips from left margin
	int tabKind;							// Sets tab kind
	int tabLead;							// Sets tab lead
};



// RTF bullets and numbering format structure
struct RTF_NUMS_FORMAT
{
	int numsLevel;							// Sets paragraph numbered level (11 is bulleted paragraph)
	int numsSpace;							// Sets paragraph text distance from bulleted char
	char numsChar;							// Sets paragraph bullet char
};



// RTF borders format structure
struct RTF_BORDERS_FORMAT
{
	int borderKind;							// Sets paragraph border kind
	int borderType;							// Sets paragraph border type
	int borderWidth;						// Sets paragraph border width in twips
	int borderColor;						// Sets paragraph border color
	int borderSpace;						// Sets border distance from paragraph
};



// RTF shading format structure
struct RTF_SHADING_FORMAT
{
	int shadingIntensity;					// Sets paragraph shading intensity
	int shadingType;						// Sets paragraph shading type
	int shadingFillColor;					// Sets paragraph shading fill color
	int shadingBkColor;						// Sets paragraph shading background color
};



// RTF character format structure
struct RTF_CHARACTER_FORMAT
{
	int animatedCharacter;					// Sets animated text
	bool boldCharacter;						// Sets text to bold
	bool capitalCharacter;					// Sets text to capital
	int backgroundColor;					// Sets text background color (the default is 0)
	int foregroundColor;					// Sets text foreground color (the default is 0)
	int scaleCharacter;						// Sets text scaling value (the default is 100)
	bool embossCharacter;					// Sets text to embossed
	int expandCharacter;					// Sets expansion or compression of the text
	int fontNumber;							// Sets font number
	int fontSize;							// Sets font size (the default is 24)
	bool italicCharacter;					// Sets text to italic
	bool engraveCharacter;					// Sets text to engrave
	int kerningCharacter;					// Sets kerning of the text
	bool outlineCharacter;					// Sets text to outline
	bool smallcapitalCharacter;				// Sets text to small capital
	bool shadowCharacter;					// Sets text shadow
	bool strikeCharacter;					// Sets text to striketrough
	bool doublestrikeCharacter;				// Sets text to double striketrough
	bool subscriptCharacter;				// Sets text to subscript
	bool superscriptCharacter;				// Sets text to superscript
	int underlineCharacter;					// Sets text to underline
};



// RTF paragraph format structure
struct RTF_PARAGRAPH_FORMAT
{
	int paragraphBreak;						// Sets paragraph break type
	bool newParagraph;						// New paragraph
	bool defaultParagraph;					// Default paragraph formatting
	int paragraphAligment;					// Sets paragraph aligment
	int firstLineIndent;					// Sets first line indent (the default is 0)
	int leftIndent;							// Sets paragraph left indent (the default is 0)
	int rightIndent;						// Sets paragraph right indent (the default is 0)
	int spaceBefore;						// Sets space before paragraph (the default is 0)
	int spaceAfter;							// Sets space after paragraph (the default is 0)
	int lineSpacing;						// Sets line spacing in paragraph
	char* paragraphText;					// Sets paragraph text
	bool tabbedText;						// Sets paragraph tabbed text
	bool tableText;							// Sets paragraph table text

	bool paragraphTabs;						// Paragraph has tabs
	struct RTF_TABS_FORMAT TABS;			// Paragraf RTF_TAB_FORMAT structure

	bool paragraphNums;						// Paragraph is numbered (bulleted)
	struct RTF_NUMS_FORMAT NUMS;			// Paragraph RTF_NUMS_FORMAT structure

	bool paragraphBorders;					// Paragraph has borders
	struct RTF_BORDERS_FORMAT BORDERS;		// Paragraph RTF_BORDERS_FORMAT structure

	bool paragraphShading;					// Paragraph has shading
	struct RTF_SHADING_FORMAT SHADING;		// Paragraph RTF_SHADING_FORMAT structure

	struct RTF_CHARACTER_FORMAT CHARACTER;	// Paragraph RTF_CHARACTER_FORMAT structure
};



// RTF table border format structure
struct RTF_TABLEBORDER_FORMAT
{
	bool border;							// Border exists
	struct RTF_BORDERS_FORMAT BORDERS;		// RTF_BORDERS_FORMAT structure
};



// RTF table row format structure
struct RTF_TABLEROW_FORMAT
{
	int rowAligment;						// Sets table row aligment
	int rowHeight;							// Sets table row height (the default is 0)
	int marginLeft;							// Sets default cell left margin
	int marginRight;						// Sets default cell right margin
	int marginTop;							// Sets default cell top margin
	int marginBottom;						// Sets default cell bottom margin
	int rowLeftMargin;						// Sets default row left margin
};



// RTF table cell format structure
struct RTF_TABLECELL_FORMAT
{
	int textVerticalAligment;						// Sets text vertical aligment
	int marginLeft;									// Sets cell left margin
	int marginRight;								// Sets cell right margin
	int marginTop;									// Sets cell top margin
	int marginBottom;								// Sets cell bottom margin
	int textDirection;								// Sets text direction

	bool cellShading;								// Cell has shading
	struct RTF_SHADING_FORMAT SHADING;				// Cell RTF_SHADING_FORMAT structure

	struct RTF_TABLEBORDER_FORMAT borderLeft;		// Cell RTF_TABLEBORDER_FORMAT structure
	struct RTF_TABLEBORDER_FORMAT borderRight;		// Cell RTF_TABLEBORDER_FORMAT structure
	struct RTF_TABLEBORDER_FORMAT borderTop;		// Cell RTF_TABLEBORDER_FORMAT structure
	struct RTF_TABLEBORDER_FORMAT borderBottom;		// Cell RTF_TABLEBORDER_FORMAT structure
};


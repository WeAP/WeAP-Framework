#include "PDFEditor.h"
//#include "Exception.h"
//#include "Error.h"

#include <podofo/podofo.h>

using namespace PoDoFo;

//using namespace WeAP::System;

namespace WeAP { namespace PDF {

PDFEditor::PDFEditor()
{

}

PDFEditor::~PDFEditor()
{
}

void PDFEditor::GenerateFile()
{
    const char* pszFilename = "/home/xzwang/WeAP-Framework/unit_test/WeAP/test.pdf";
    PoDoFo::PdfStreamedDocument document( pszFilename );


    PoDoFo::PdfPainter painter;
    PoDoFo::PdfPage* pPage;

    PoDoFo::PdfFont* pFont;

    try 
    {
        pPage = document.CreatePage( PdfPage::CreateStandardPageSize( ePdfPageSize_A4 ) );

        if( !pPage )
        {
            PODOFO_RAISE_ERROR( ePdfError_InvalidHandle );
        }

        painter.SetPage( pPage );


        pFont = document.CreateFont( "Arial" );


        if( !pFont )
        {
            PODOFO_RAISE_ERROR( ePdfError_InvalidHandle );
        }


        pFont->SetFontSize( 18.0 );


        painter.SetFont( pFont );


        painter.DrawText( 56.69, pPage->GetPageSize().GetHeight() - 56.69, "Hello World!" );


        painter.FinishPage();

        document.GetInfo()->SetCreator ( PdfString("examplahelloworld - A PoDoFo test application") );
        document.GetInfo()->SetAuthor  ( PdfString("Dominik Seichter") );
        document.GetInfo()->SetTitle   ( PdfString("Hello World") );
        document.GetInfo()->SetSubject ( PdfString("Testing the PoDoFo PDF Library") );
        document.GetInfo()->SetKeywords( PdfString("Test;PDF;Hello World;") );


        document.Close();
    } 
    catch ( PdfError & e ) 
    {

        try 
        {
            painter.FinishPage();
        } catch( ... ) 
        {

        }

        throw e;
    }

}





}}


/*
 * This program source code file is part of KiCad, a free EDA CAD application.
 *
 * Copyright (C) 2020 KiCad Developers, see AUTHORS.txt for contributors.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, you may find one here:
 * http://www.gnu.org/licenses/old-licenses/gpl-2.0.html
 * or you may search the http://www.gnu.org website for the version 2 license,
 * or you may write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA
 */

#ifndef DIALOG_LABEL_EDITOR_H_
#define DIALOG_LABEL_EDITOR_H_

#include <widgets/unit_binder.h>
#include <sch_text.h>
#include <sch_validators.h>
#include <dialog_edit_label_base.h>


class SCH_EDIT_FRAME;
class SCH_TEXT;
class SCINTILLA_TRICKS;


class DIALOG_LABEL_EDITOR : public DIALOG_LABEL_EDITOR_BASE
{
public:
    DIALOG_LABEL_EDITOR( SCH_EDIT_FRAME* parent, SCH_TEXT* aTextItem );
    ~DIALOG_LABEL_EDITOR();

    void SetTitle( const wxString& aTitle ) override
    {
        // This class is shared for numerous tasks: a couple of single line labels and
        // multi-line text fields.  Since the desired size of the multi-line text field editor
        // is often larger, we retain separate sizes based on the dialog titles.
        switch( m_CurrentText->Type() )
        {
        case SCH_GLOBAL_LABEL_T:
        case SCH_HIER_LABEL_T:
        case SCH_LABEL_T:
            // labels can share retained settings probably.
            break;

        default:
            m_hash_key = TO_UTF8( aTitle );
            m_hash_key += typeid(*this).name();
        }

        DIALOG_LABEL_EDITOR_BASE::SetTitle( aTitle );
    }

private:
    void onScintillaCharAdded( wxStyledTextEvent &aEvent );

    void OnEnterKey( wxCommandEvent& aEvent ) override;
    void OnFormattingHelp( wxHyperlinkEvent& aEvent ) override;

    bool TransferDataToWindow() override;
    bool TransferDataFromWindow() override;

    wxString convertKIIDsToReferences( const wxString& aSource ) const;

    wxString convertReferencesToKIIDs( const wxString& aSource ) const;

    SCH_EDIT_FRAME*       m_Parent;
    SCH_TEXT*             m_CurrentText;
    wxWindow*             m_activeTextCtrl;
    wxTextEntry*          m_activeTextEntry;
    UNIT_BINDER           m_textSize;
    SCH_NETNAME_VALIDATOR m_netNameValidator;
    SCINTILLA_TRICKS*     m_scintillaTricks;
};



#endif // DIALOG_LABEL_EDITOR_H_

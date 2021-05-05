/*
  ==============================================================================

    ChordTable.cpp
    Created: 2 May 2021 6:49:01pm
    Author:  Matt

  ==============================================================================
*/

#include "ChordTable.h"
namespace view
{
void ChordTable::initColumns()
{
	auto& header = getHeader();
	auto scale = GetController().GetHomeScale();
	const auto rootNote = GetController().GetRootNote();

	int pitch = rootNote.pitch;
	// Column IDs must start at 1.
	for ( int i = 0; i < scale.intervals.size(); ++i )
	{
		Note note( { pitch } );
		DBG( note.GetNoteDescr() );
		header.addColumn ( note.GetNoteDescr(), i + 1, std::max(20,getWidth()/7), /*minimumWidth=*/30, /*maximumWidth=*/-1/*, propertyFlags=defaultFlags, insertIndex=-1*/);
		pitch += scale.intervals[i];
	}
}
}

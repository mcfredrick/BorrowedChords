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
		int num = scale.intervals.size();
		int pitch = rootNote.pitch;
		auto colWidth = std::max( 20, getWidth() / ( num + 1 ) );

		header.addColumn( "Scale" , 1, colWidth, /*minimumWidth=*/30, /*maximumWidth=*/-1/*, propertyFlags=defaultFlags, insertIndex=-1*/);

		// Column IDs must start at 1.
		for (int i = 0; i < num; ++i)
		{
			Note note({ pitch });
			DBG(note.GetNoteDescr());
			header.addColumn(note.GetNoteDescr(), i + 2, colWidth, /*minimumWidth=*/30, /*maximumWidth=*/-1/*, propertyFlags=defaultFlags, insertIndex=-1*/);
			pitch += scale.intervals[i];
		}
	}
};

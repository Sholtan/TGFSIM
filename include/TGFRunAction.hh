#ifndef TGFRunAction_HH
#define TGFRunAction_HH

#include "G4UserRunAction.hh"
#include "G4Run.hh"
#include "G4AnalysisManager.hh"

class TGFRunAction: public G4UserRunAction
{
public:
	TGFRunAction();
	~TGFRunAction();


	virtual void BeginOfRunAction(const G4Run*);
	virtual void EndOfRunAction(const G4Run*);

};

#endif




#ifndef TGFEventAction_HH
#define TGFEventAction_HH

#include "G4UserEventAction.hh"
#include "G4Event.hh"
#include "G4AnalysisManager.hh"

#include "TGFRunAction.hh"

#include "TGFEventInformation.hh"


class TGFEventAction : public G4UserEventAction
{
public:
	TGFEventAction(TGFRunAction*);
	~TGFEventAction();

	void AddCount() { fCount += 1; }

	virtual void BeginOfEventAction(const G4Event*);
	virtual void EndOfEventAction(const G4Event*);

	std::map<int, std::vector<double>> fparticle_info;


private:
	G4int fCount;
};

#endif



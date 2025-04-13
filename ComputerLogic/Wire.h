#pragma once
class Wire
{
private:
	bool state = false;
	int objId1;
	int objId2;
public:
	Wire(int objId1, int objId2) : objId1(objId1), objId2(objId2) {};
	bool GetState() const { return state; }
	void SetState(bool newState) { state = newState; }

	int GetObjId1() const { return objId1; }
	int GetObjId2() const { return objId2; }
};


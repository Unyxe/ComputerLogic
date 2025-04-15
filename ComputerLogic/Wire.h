#pragma once
class Wire
{
private:
	bool state = false;
	int objId1;
	int objId2;
	int index1;
	int index2;
public:
	Wire(int objId1, int objId2, int index1, int index2) : objId1(objId1), objId2(objId2), index1(index1), index2(index2) {};
	bool GetState() const { return state; }
	void SetState(bool newState) { state = newState; }

	int GetObjId1() const { return objId1; }
	int GetObjId2() const { return objId2; }
	int GetIndex1() const { return index1; }
	int GetIndex2() const { return index2; }
};


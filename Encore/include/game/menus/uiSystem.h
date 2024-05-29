#pragma once
#include <string>
#include <vector>
#include <map>
#include <stdexcept>
#include "raylib.h"

class Element {
public:
	std::string elementID = "";
	bool disabled;
	virtual ~Element() = default;
	void SetID(std::string id) {
		elementID = id;
	}
	virtual void Draw() = 0;
	virtual void Update() = 0;
};

 class Button : public Element{
 private:
	 bool hovered = false;
	 bool clicked = false;
 public:
	 std::string text = "";
	 Rectangle bounds{ 0,0,0,0 };
	 Button(std::string id, Rectangle rect, std::string buttonText) {
		 SetID(id);
		 bounds = rect;
		 text = buttonText;
	 }
	 void Draw() override {
		 DrawRectangle(bounds.x, bounds.y, bounds.width, bounds.height, hovered ? BLUE : GRAY);
		 DrawRectangle(bounds.x+5, bounds.y+5, bounds.width-10, bounds.height-10, clicked?BLACK:ColorAlpha(WHITE,0));
		 DrawText(text.c_str(), bounds.x + ((bounds.width - MeasureText(text.c_str(), 25)) / 2.0), bounds.y + (bounds.height / 2.0) - 12.5,25,WHITE);
	 }
	 void Update() override {
		 hovered = CheckCollisionPointRec(GetMousePosition(), bounds);
		 clicked = hovered && IsMouseButtonReleased(MOUSE_LEFT_BUTTON);
	 }
	 bool isClicked() const{
		 return clicked;
	 }
	 bool isHovered() const{
		 return hovered;
	 }
 };

 class Toggle : public Element {
 private:
	 bool hovered = false;
 public:
	 bool state = false;
	 std::string text = "";
	 Rectangle bounds{ 0,0,0,0 };
	 Toggle(std::string id, Rectangle rect, std::string buttonText) {
		 SetID(id);
		 bounds = rect;
		 text = buttonText;
	 }
	 void Draw() override {
		 DrawRectangle(bounds.x, bounds.y, bounds.width, bounds.height, hovered ? BLUE : GRAY);
		 DrawRectangle(bounds.x + 5, bounds.y + 5, bounds.width - 10, bounds.height - 10, state ? BLACK : ColorAlpha(WHITE, 0));
		 DrawText(text.c_str(), bounds.x + ((bounds.width - MeasureText(text.c_str(), 25)) / 2.0), bounds.y + (bounds.height / 2.0) - 12.5, 25, WHITE);
	 }
	 void Update() override {
		 hovered = CheckCollisionPointRec(GetMousePosition(), bounds);
		 if (hovered && IsMouseButtonReleased(MOUSE_LEFT_BUTTON)) {
			 state = !state;
		 }
	 }
	 bool getState() const {
		 return state;
	 }
	 bool isHovered() const {
		 return hovered;
	 }
 };

 class ToggleGroup : public Element {
 private:
	 std::vector<Toggle*> toggles;
 public:
	 int activeIndex = -1;
	 ToggleGroup(const std::string& id) {
		 SetID(id);
	 }

	 void AddToggle(Toggle* toggle) {
		 toggles.push_back(toggle);
	 }

	 void Draw() override {
		 for (auto& toggle : toggles) {
			 toggle->Draw();
		 }
	 }

	 void Update() override {
		 for (int i = 0; i < toggles.size(); ++i) {
			 toggles[i]->Update();
			 if (toggles[i]->getState()) {
				 if (i != activeIndex) {
					 if (activeIndex != -1) {
						 toggles[activeIndex]->state = false; // Deselect the previously active toggle
					 }
					 activeIndex = i;
				 }
			 }
		 }
		 if (activeIndex != -1) {
			 toggles[activeIndex]->state = true;
		 }
	 }
	 ~ToggleGroup() override{
		 for (auto& t : toggles) {
			 delete t;
		 }
	 }
 };




class Row {
public:
	std::string defaultElementID;
	std::vector<Element*> elements;
	void Update() {
		for (auto element : elements) {
			element->Update();
		}
	}
	void Draw() {
		for (auto element : elements) {
			element->Draw();
		}
	}
	~Row() {
		for (auto element : elements) {
			delete element;
		}
	}
};


class UI{
private:
	std::map < std::string, std::pair<int, int>> elementMap;
public:
	std::vector<Row*> rows; 
	void AddElement(int row,Element* element) 
	{
		elementMap[element->elementID] = { row,rows[row]->elements.size() };
		rows[row]->elements.push_back(element);
	}
	Element* GetElement(std::string id) {
		auto it = elementMap.find(id);
		if (it == elementMap.end()) {
			throw std::invalid_argument("Element ID not found: " + id);
		}
		auto [rowIndex, elementIndex] = it->second;
		return rows[rowIndex]->elements[elementIndex];
	}
	Button* GetButton(std::string id) {
		return dynamic_cast<Button*>(GetElement(id));
	}
	Toggle* GetToggle(std::string id) {
		return dynamic_cast<Toggle*>(GetElement(id));
	}
	ToggleGroup* GetToggleGroup(std::string id) {
		return dynamic_cast<ToggleGroup*>(GetElement(id));
	}
	void AddRow() {
		rows.push_back(new Row);
	}
	void Update() {
		for (auto& row : rows) {
			row->Update();
		}
	}void Draw() {
		for (auto& row : rows) {
			row->Draw();
		}
	}
	~UI() {
		for (auto row : rows) {
			delete row;
		}
	}
};
#ifndef __mouserptparser_h__
#define __mouserptparser_h__

class MouseRptParser : public MouseReportParser {
  protected:
    virtual void OnMouseMove(MOUSEINFO *mi);
    virtual void OnLeftButtonUp(MOUSEINFO *mi);
    virtual void OnLeftButtonDown(MOUSEINFO *mi);
    virtual void OnRightButtonUp(MOUSEINFO *mi);
    virtual void OnRightButtonDown(MOUSEINFO *mi);
    virtual void OnMiddleButtonUp(MOUSEINFO *mi);
    virtual void OnMiddleButtonDown(MOUSEINFO *mi);
};

void MouseRptParser::OnMouseMove(MOUSEINFO *mi) {
  Serial.print(F("dx="));
  Serial.print(mi->dX, DEC);
  Serial.print(F(" dy="));
  Serial.println(mi->dY, DEC);
};

void MouseRptParser::OnLeftButtonUp(MOUSEINFO *mi) {
  Serial.println(F("L Butt Up"));
};

void MouseRptParser::OnLeftButtonDown(MOUSEINFO *mi) {
  Serial.println(F("L Butt Dn"));
};

void MouseRptParser::OnRightButtonUp(MOUSEINFO *mi) {
  Serial.println(F("R Butt Up"));
};

void MouseRptParser::OnRightButtonDown(MOUSEINFO *mi) {
  Serial.println(F("R Butt Dn"));
};

void MouseRptParser::OnMiddleButtonUp(MOUSEINFO *mi) {
  Serial.println(F("M Butt Up"));
};

void MouseRptParser::OnMiddleButtonDown(MOUSEINFO *mi) {
  Serial.println(F("M Butt Dn"));
};

#endif

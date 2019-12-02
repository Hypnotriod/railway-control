/*
 * ui.h
 *
 * Created: 25.11.2019 21:04:45
 *  Author: Ilya Pikin
 */ 


#ifndef UI_H_
#define UI_H_

#define UI_MANUAL_CONTROL_MODE_DDR		DDRD
#define UI_MANUAL_CONTROL_MODE_PIN		PIND
#define UI_MANUAL_CONTROL_MODE_PORT		PORTD
#define UI_MANUAL_CONTROL_MODE_INDEX	0

#define UI_KNOBS_DEAD_ZONE			0.05f
#define UI_KNOBS_MIN_VALUE			0.3f
#define UI_KNOBS_NUM				6
#define UI_KNOBS_DEFAULT_ADC_VALUE	ADC_VALUE_MID

enum UI_KnobDirectionEnum
{
	UI_KNOB_DIR_BOUTH_WAYS,
	UI_KNOB_DIR_UP,
	UI_KNOB_DIR_DOWN	
};

#define UI_IsManualControlModeOn()	((UI_MANUAL_CONTROL_MODE_PIN & (1 << UI_MANUAL_CONTROL_MODE_INDEX)) == 0)

void UI_Init(void);
void UI_Update(void);
void UI_ResetKnobs(void);

#endif /* UI_H_ */
#define FLAG_ACTIVE_DEBUG false

#include <Arduino.h>
#include <Wiegand.h>
#include "config.h"
#include "opener.h"
#include "time_mc.h"

OpenerExc opener(0x4, 0xC);
WIEGAND wiegand;
TimeMC timeMC;

void setup()
{
#if (FLAG_ACTIVE_DEBUG == true)
  Serial.begin(115200);
  Serial.println(F("\n\nDEBUG: DEVICE > setup"));
#endif
  wiegand.begin();
#if (FLAG_ACTIVE_DEBUG == true)
  Serial.println(F("DEBUG: DEVICE > begin"));
#endif
}

void loop()
{
  timeMC.update();
  opener.relay.process(timeMC.ms);
  opener.pressingOpen(timeMC.ms);
  if (wiegand.available())
  {
    unsigned long key = wiegand.getCode();
#if (FLAG_ACTIVE_DEBUG == true)
    Serial.print(F("DEBUG: WIEGAND > key:"));
    Serial.println(key);
#endif
    if (key < 9999)
    {
      return;
    }
    switch (key)
    {
    case MASTER_KEY_1:
      break;
    case MASTER_KEY_2:
      break;
    case MASTER_KEY_3:
      break;
    case MASTER_KEY_4:
      break;
    case MASTER_KEY_5:
      break;
    case MASTER_KEY_6:
      break;
    case MASTER_KEY_7:
      break;
    case MASTER_KEY_8:
      break;
    case MASTER_KEY_9:
      break;
    case MASTER_KEY_10:
      break;
    case MASTER_KEY_11:
      break;
    case MASTER_KEY_12:
      break;
    case MASTER_KEY_13:
      break;
    case MASTER_KEY_14:
      break;
    case MASTER_KEY_15:
      break;
    case MASTER_KEY_16:
      break;
    case MASTER_KEY_17:
      break;
    case MASTER_KEY_18:
      break;
    case MASTER_KEY_19:
      break;
    case MASTER_KEY_20:
      break;
    case MASTER_KEY_21:
      break;
    case MASTER_KEY_22:
      break;
    case MASTER_KEY_23:
      break;
    case MASTER_KEY_24:
      break;
    case MASTER_KEY_25:
      break;
    case MASTER_KEY_26:
      break;
    case MASTER_KEY_27:
      break;
    case MASTER_KEY_28:
      break;
    case MASTER_KEY_29:
      break;
    case MASTER_KEY_30:
      break;
    case MASTER_KEY_31:
      break;
    case MASTER_KEY_32:
      break;
    case MASTER_KEY_33:
      break;
    case MASTER_KEY_34:
      break;
    case MASTER_KEY_35:
      break;
    case MASTER_KEY_36:
      break;
    case MASTER_KEY_37:
      break;
    case MASTER_KEY_38:
      break;
    case MASTER_KEY_39:
      break;
    case MASTER_KEY_40:
      break;
    case MASTER_KEY_41:
      break;
    case MASTER_KEY_42:
      break;
    case MASTER_KEY_43:
      break;
    case MASTER_KEY_44:
      break;
    case MASTER_KEY_45:
      break;
    case MASTER_KEY_46:
      break;
    case MASTER_KEY_47:
      break;
    case MASTER_KEY_48:
      break;
    case MASTER_KEY_49:
      break;
    case MASTER_KEY_50:
      break;
    case MASTER_KEY_51:
      break;
    case MASTER_KEY_52:
      break;
    case MASTER_KEY_53:
      break;
    case MASTER_KEY_54:
      break;
    case MASTER_KEY_55:
      break;
    case MASTER_KEY_56:
      break;
    case MASTER_KEY_57:
      break;
    case MASTER_KEY_58:
      break;
    case MASTER_KEY_59:
      break;
    case MASTER_KEY_60:
      break;
    case MASTER_KEY_61:
      break;
    case MASTER_KEY_62:
      break;
    case MASTER_KEY_63:
      break;
    case MASTER_KEY_64:
      break;
    case MASTER_KEY_65:
      break;
    case MASTER_KEY_66:
      break;
    case MASTER_KEY_67:
      break;
    case MASTER_KEY_68:
      break;
    case MASTER_KEY_69:
      break;
    case MASTER_KEY_70:
      break;
    case MASTER_KEY_71:
      break;
    case MASTER_KEY_72:
      break;
    case MASTER_KEY_73:
      break;
    case MASTER_KEY_74:
      break;
    case MASTER_KEY_75:
      break;
    case MASTER_KEY_76:
      break;
    case MASTER_KEY_77:
      break;
    case MASTER_KEY_78:
      break;
    case MASTER_KEY_79:
      break;
    case MASTER_KEY_80:
      break;
    case MASTER_KEY_81:
      break;
    case MASTER_KEY_82:
      break;
    case MASTER_KEY_83:
      break;
    case MASTER_KEY_84:
      break;
    case MASTER_KEY_85:
      break;
    case MASTER_KEY_86:
      break;
    case MASTER_KEY_87:
      break;
    case MASTER_KEY_88:
      break;
    case MASTER_KEY_89:
      break;
    case MASTER_KEY_90:
      break;
    case MASTER_KEY_91:
      break;
    case MASTER_KEY_92:
      break;
    case MASTER_KEY_93:
      break;
    case MASTER_KEY_94:
      break;
    case MASTER_KEY_95:
      break;
    case MASTER_KEY_96:
      break;
    case MASTER_KEY_97:
      break;
    case MASTER_KEY_98:
      break;
    case MASTER_KEY_99:
      break;
    case MASTER_KEY_100:
      break;
    default:
      return;
    }
#if (FLAG_ACTIVE_DEBUG == true)
    Serial.print(F("DEBUG: WIEGAND > relay active"));
#endif
    opener.relay.active(timeMC.ms);
  }
}
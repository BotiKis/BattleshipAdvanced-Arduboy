#include "BACharacter.h"

BAPlayer::BAPlayer(BACharacterData data){
  charData = data;
}

BACharacterData BAPlayer::getCharacterData(){
  return charData;
}


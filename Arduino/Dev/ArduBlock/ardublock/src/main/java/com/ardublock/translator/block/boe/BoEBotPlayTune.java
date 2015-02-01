package com.ardublock.translator.block.boe;

import com.ardublock.translator.Translator;

public class BoEBotPlayTune extends BoEBotBlock {

	protected final static String MOTION = "playTune";

	public BoEBotPlayTune(Long blockId, Translator translator, String codePrefix, String codeSuffix, String label)
	{
		super(blockId, translator, codePrefix, codeSuffix, label, MOTION);
	}
}	
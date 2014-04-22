package com.ardublock.translator.block;

import com.ardublock.translator.Translator;

public class WhileBlock extends TranslatorBlock
{

	public WhileBlock(Long blockId, Translator translator, String codePrefix, String codeSuffix, String label)
	{
		super(blockId, translator);
	}
	
	@Override
	public String toCode() throws Exception
	{
		String ret = "\twhile ( ";
		TranslatorBlock translatorBlock = this.getRequiredTranslatorBlockAtSocket(0);
		ret = ret + translatorBlock.toCode();
		ret = ret + " )\n\t{\n";
		translatorBlock = getTranslatorBlockAtSocket(1);
		while (translatorBlock != null)
		{
			ret = ret + "\t"+translatorBlock.toCode();
			translatorBlock = translatorBlock.nextTranslatorBlock();
		}
		ret = ret + "\t}\n\n";
		return ret;
	}

}

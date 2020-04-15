<GameFile>
  <PropertyGroup Name="MainScene" Type="Scene" ID="a2ee0952-26b5-49ae-8bf9-4f1d6279b798" Version="3.10.0.0" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="20" Speed="1.0000">
        <Timeline ActionTag="2034891902" Property="Position">
          <PointFrame FrameIndex="0" X="79.9224" Y="121.6309">
            <EasingData Type="0" />
          </PointFrame>
          <PointFrame FrameIndex="10" X="264.9329" Y="117.2948">
            <EasingData Type="0" />
          </PointFrame>
          <PointFrame FrameIndex="20" X="56.7962" Y="125.9672">
            <EasingData Type="0" />
          </PointFrame>
        </Timeline>
        <Timeline ActionTag="1352014992" Property="Position">
          <PointFrame FrameIndex="0" X="94.3746" Y="561.0342">
            <EasingData Type="0" />
          </PointFrame>
          <PointFrame FrameIndex="10" X="893.6781" Y="558.1454">
            <EasingData Type="0" />
          </PointFrame>
          <PointFrame FrameIndex="20" X="65.4659" Y="562.4825">
            <EasingData Type="0" />
          </PointFrame>
        </Timeline>
        <Timeline ActionTag="-819408147" Property="Position">
          <PointFrame FrameIndex="0" X="84.2583" Y="345.6679">
            <EasingData Type="0" />
          </PointFrame>
          <PointFrame FrameIndex="10" X="478.8517" Y="341.3320">
            <EasingData Type="0" />
          </PointFrame>
          <PointFrame FrameIndex="20" X="64.0233" Y="345.6690">
            <EasingData Type="0" />
          </PointFrame>
        </Timeline>
        <Timeline ActionTag="985229122" Property="Position">
          <PointFrame FrameIndex="13" X="691.3179" Y="315.3187">
            <EasingData Type="0" />
          </PointFrame>
        </Timeline>
        <Timeline ActionTag="985229122" Property="Scale">
          <ScaleFrame FrameIndex="13" X="8.8554" Y="6.7816">
            <EasingData Type="0" />
          </ScaleFrame>
        </Timeline>
      </Animation>
      <ObjectData Name="Scene" ctype="GameNodeObjectData">
        <Size X="1280.0000" Y="720.0000" />
        <Children>
          <AbstractNodeData Name="Particle_1" ActionTag="2034891902" Tag="5" IconVisible="True" LeftMargin="56.7962" RightMargin="1223.2039" TopMargin="594.0328" BottomMargin="125.9672" ctype="ParticleObjectData">
            <Size X="0.0000" Y="0.0000" />
            <AnchorPoint />
            <Position X="56.7962" Y="125.9672" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.0444" Y="0.1750" />
            <PreSize X="0.0000" Y="0.0000" />
            <FileData Type="Default" Path="Default/defaultParticle.plist" Plist="" />
            <BlendFunc Src="775" Dst="1" />
          </AbstractNodeData>
          <AbstractNodeData Name="Particle_2" ActionTag="1352014992" Tag="6" IconVisible="True" LeftMargin="65.4659" RightMargin="1214.5341" TopMargin="157.5175" BottomMargin="562.4825" ctype="ParticleObjectData">
            <Size X="0.0000" Y="0.0000" />
            <AnchorPoint />
            <Position X="65.4659" Y="562.4825" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.0511" Y="0.7812" />
            <PreSize X="0.0000" Y="0.0000" />
            <FileData Type="Default" Path="Default/defaultParticle.plist" Plist="" />
            <BlendFunc Src="775" Dst="1" />
          </AbstractNodeData>
          <AbstractNodeData Name="Particle_3" ActionTag="-819408147" Tag="7" IconVisible="True" LeftMargin="64.0233" RightMargin="1215.9767" TopMargin="374.3310" BottomMargin="345.6690" ctype="ParticleObjectData">
            <Size X="0.0000" Y="0.0000" />
            <AnchorPoint />
            <Position X="64.0233" Y="345.6690" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.0500" Y="0.4801" />
            <PreSize X="0.0000" Y="0.0000" />
            <FileData Type="Default" Path="Default/defaultParticle.plist" Plist="" />
            <BlendFunc Src="775" Dst="1" />
          </AbstractNodeData>
          <AbstractNodeData Name="Button_2" ActionTag="985229122" Tag="9" IconVisible="False" LeftMargin="668.3179" RightMargin="565.6821" TopMargin="386.6813" BottomMargin="297.3187" TouchEnable="True" FontSize="18" ButtonText="Hello" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="16" Scale9Height="14" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
            <Size X="46.0000" Y="36.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="691.3179" Y="315.3187" />
            <Scale ScaleX="8.8554" ScaleY="6.7816" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.5401" Y="0.4379" />
            <PreSize X="0.0359" Y="0.0500" />
            <TextColor A="255" R="65" G="65" B="70" />
            <DisabledFileData Type="Default" Path="Default/Button_Disable.png" Plist="" />
            <PressedFileData Type="Default" Path="Default/Button_Press.png" Plist="" />
            <NormalFileData Type="Default" Path="Default/Button_Normal.png" Plist="" />
            <OutlineColor A="255" R="255" G="0" B="0" />
            <ShadowColor A="255" R="110" G="110" B="110" />
          </AbstractNodeData>
          <AbstractNodeData Name="HelloWorld_1" ActionTag="-555796224" Tag="7" IconVisible="False" LeftMargin="-177.0000" RightMargin="497.0000" TopMargin="-79.0007" BottomMargin="159.0007" ctype="SpriteObjectData">
            <Size X="960.0000" Y="640.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="303.0000" Y="479.0007" />
            <Scale ScaleX="0.2771" ScaleY="0.3219" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.2367" Y="0.6653" />
            <PreSize X="0.7500" Y="0.8889" />
            <FileData Type="Normal" Path="HelloWorld.png" Plist="" />
            <BlendFunc Src="770" Dst="771" />
          </AbstractNodeData>
        </Children>
      </ObjectData>
    </Content>
  </Content>
</GameFile>
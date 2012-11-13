#include "StdAfx.h"
#include "UIChartView.h"



namespace UiLib
{
	//************************************
	// ��������: CChartSeries
	// ��������: 
	// ������Ϣ: LPCTSTR _LegendText
	// ������Ϣ: LPCTSTR _SeriesColorA
	// ������Ϣ: LPCTSTR _SeriesColorB
	// ����˵��: 
	//************************************
	CChartSeries::CChartSeries( LPCTSTR _LegendText,LPCTSTR _SeriesColorA,LPCTSTR _SeriesColorB /*= NULL*/ ) : 
		m_bIsVisible(true),			//�Ƿ���ʾ��ǰ�����ݱ���ͼ��
		m_uSeriesFondId(0),			//ͼ������ID
		m_dSeriesColorA(0),			//����ͼ����ɫ�����俪ʼɫ
		m_dSeriesColorB(0),			//����ͼ����ɫ���������ɫ����ͼ�����Ը�ֵ
		m_pChartView(NULL)			//ͼ��ָ��
	{
		m_sLegendText	= _LegendText;

		SetSeriesColor(_SeriesColorA,_SeriesColorB);
	}

	//************************************
	// ��������: CChartSeries
	// ��������: 
	// ������Ϣ: LPCTSTR _LegendText
	// ������Ϣ: DWORD _SeriesColorA
	// ������Ϣ: DWORD _SeriesColorB
	// ����˵��: 
	//************************************
	CChartSeries::CChartSeries( LPCTSTR _LegendText,DWORD _SeriesColorA,DWORD _SeriesColorB ) : 
		m_bIsVisible(true),			//�Ƿ���ʾ��ǰ�����ݱ���ͼ��
		m_uSeriesFondId(0),			//ͼ������ID
		m_dSeriesColorA(0),			//����ͼ����ɫ�����俪ʼɫ
		m_dSeriesColorB(0),			//����ͼ����ɫ���������ɫ����ͼ�����Ը�ֵ
		m_pChartView(NULL)			//ͼ��ָ��
	{
		m_sLegendText	= _LegendText;

		SetSeriesColor(_SeriesColorA,_SeriesColorB);
	}

	//************************************
	// ��������: ~CChartSeries
	// ��������: 
	// ������Ϣ: void
	// ����˵��: 
	//************************************
	CChartSeries::~CChartSeries( void )
	{
		RemoveSeriesDataAll();
	}

	//************************************
	// ��������: SetLegendText
	// ��������: void
	// ������Ϣ: LPCTSTR _LegendText
	// ����˵��: 
	//************************************
	void CChartSeries::SetLegendText( LPCTSTR _LegendText )
	{
		m_sLegendText = _LegendText;

		if(m_pChartView)
			m_pChartView->CalLegendSize(this);
		Invalidate();
	}

	//************************************
	// ��������: GetLegendText
	// ��������: LPCTSTR
	// ����˵��: 
	//************************************
	LPCTSTR CChartSeries::GetLegendText()
	{
		return m_sLegendText.GetData();
	}

	//************************************
	// ��������: SetSeriesColor
	// ��������: void
	// ������Ϣ: LPCTSTR _SeriesColorA
	// ������Ϣ: LPCTSTR _SeriesColorB
	// ����˵��: 
	//************************************
	void CChartSeries::SetSeriesColor( LPCTSTR _SeriesColorA,LPCTSTR _SeriesColorB )
	{
		if(_SeriesColorA){
			if( *_SeriesColorA == _T('#'))
				_SeriesColorA = ::CharNext(_SeriesColorA);
			LPTSTR pstr = NULL;
			m_dSeriesColorA = _tcstoul(_SeriesColorA, &pstr, 16);
		}

		if(_SeriesColorB){
			if( *_SeriesColorB == _T('#'))
				_SeriesColorB = ::CharNext(_SeriesColorB);
			LPTSTR pstr = NULL;
			m_dSeriesColorB = _tcstoul(_SeriesColorB, &pstr, 16);
		}
		Invalidate();
	}

	//************************************
	// ��������: SetSeriesColor
	// ��������: void
	// ������Ϣ: DWORD _SeriesColorA
	// ������Ϣ: DWORD _SeriesColorB
	// ����˵��: 
	//************************************
	void CChartSeries::SetSeriesColor( DWORD _SeriesColorA,DWORD _SeriesColorB )
	{
		m_dSeriesColorA = _SeriesColorA;
		m_dSeriesColorB	= _SeriesColorB;
		Invalidate();
	}

	//************************************
	// ��������: GetSeriesColorA
	// ��������: DWORD
	// ����˵��: 
	//************************************
	DWORD CChartSeries::GetSeriesColorA()
	{
		return m_dSeriesColorA;
	}

	//************************************
	// ��������: GetSeriesColorB
	// ��������: DWORD
	// ����˵��: 
	//************************************
	DWORD CChartSeries::GetSeriesColorB()
	{
		return m_dSeriesColorB;
	}

	//************************************
	// ��������: AddSeriesData
	// ��������: bool
	// ������Ϣ: CChartItem * _ChartItem
	// ����˵��: 
	//************************************
	bool CChartSeries::AddSeriesData( CChartItem* _ChartItem )
	{
		bool nRet = m_rSeriesData.Add(_ChartItem);
		Invalidate();
		return nRet;
	}

	//************************************
	// ��������: AddSeriesData
	// ��������: bool
	// ������Ϣ: double _DataValue
	// ����˵��: 
	//************************************
	bool CChartSeries::AddSeriesData( double _DataValue )
	{
		bool nRet = m_rSeriesData.Add(new CChartItem(_DataValue));
		Invalidate();
		return nRet;
	}

	//************************************
	// ��������: SetSeriesData
	// ��������: bool
	// ������Ϣ: int _Index
	// ������Ϣ: CChartItem * _ChartItem
	// ����˵��: 
	//************************************
	bool CChartSeries::SetSeriesData( int _Index,CChartItem* _ChartItem )
	{
		bool nRet = m_rSeriesData.SetAt(_Index,_ChartItem);
		Invalidate();
		return nRet;
	}

	//************************************
	// ��������: SetSeriesData
	// ��������: bool
	// ������Ϣ: int _Index
	// ������Ϣ: double _DataValue
	// ����˵��: 
	//************************************
	bool CChartSeries::SetSeriesData( int _Index,double _DataValue )
	{
		bool nRet = m_rSeriesData.SetAt(_Index,new CChartItem(_DataValue));
		Invalidate();
		return nRet;
	}

	//************************************
	// ��������: InsertSeriesData
	// ��������: bool
	// ������Ϣ: int _Index
	// ������Ϣ: CChartItem * _ChartItem
	// ����˵��: 
	//************************************
	bool CChartSeries::InsertSeriesData( int _Index,CChartItem* _ChartItem )
	{
		bool nRet = m_rSeriesData.InsertAt(_Index,_ChartItem);
		Invalidate();
		return nRet;
	}

	//************************************
	// ��������: InsertSeriesData
	// ��������: bool
	// ������Ϣ: int _Index
	// ������Ϣ: double _DataValue
	// ����˵��: 
	//************************************
	bool CChartSeries::InsertSeriesData( int _Index,double _DataValue )
	{
		bool nRet = m_rSeriesData.InsertAt(_Index,new CChartItem(_DataValue));
		Invalidate();
		return nRet;
	}

	//************************************
	// ��������: RemoveSeriesDataAt
	// ��������: bool
	// ������Ϣ: int _Index
	// ����˵��: 
	//************************************
	bool CChartSeries::RemoveSeriesDataAt( int _Index )
	{
		CChartItem* pItem = m_rSeriesData.GetAt(_Index);
		if(pItem && m_rSeriesData.Remove(_Index)){
			delete pItem;
			pItem = NULL;

			Invalidate();
			return true;
		}
		return false;
	}

	//************************************
	// ��������: RemoveSeriesDataAll
	// ��������: void
	// ����˵��: 
	//************************************
	void CChartSeries::RemoveSeriesDataAll()
	{
		for(int iIndex = 0;iIndex < m_rSeriesData.GetSize();iIndex++){
			RemoveSeriesDataAt(iIndex);
		}
		Invalidate();
	}

	//************************************
	// ��������: GetSeriesData
	// ��������: CChartItem*
	// ������Ϣ: int _Index
	// ����˵��: 
	//************************************
	CChartItem* CChartSeries::GetSeriesData( int _Index )
	{
		return m_rSeriesData.GetAt(_Index);
	}
	
	//************************************
	// ��������: GetDataCount
	// ��������: int
	// ����˵��: 
	//************************************
	int CChartSeries::GetDataCount()
	{
		return m_rSeriesData.GetSize();
	}

	//************************************
	// ��������: SetVisible
	// ��������: void
	// ������Ϣ: bool _Visible
	// ����˵��: 
	//************************************
	void CChartSeries::SetVisible( bool _Visible )
	{
		m_bIsVisible = _Visible;
		Invalidate();
	}

	//************************************
	// ��������: GetVisible
	// ��������: bool
	// ����˵��: 
	//************************************
	bool CChartSeries::GetVisible()
	{
		return m_bIsVisible;
	}

	//************************************
	// ��������: SetChartViewObj
	// ��������: void
	// ������Ϣ: CChartViewUI * _pChartViewUI
	// ����˵��: 
	//************************************
	void CChartSeries::SetChartViewObj( CChartViewUI* _pChartViewUI )
	{
		m_pChartView = _pChartViewUI;
	}

	//************************************
	// ��������: Invalidate
	// ��������: void
	// ����˵��: 
	//************************************
	void CChartSeries::Invalidate()
	{
		if(m_pChartView)
			m_pChartView->Invalidate();
	}

	/**************************************************************************************************************************************************************************************************/
	/*
	/**************************************************************************************************************************************************************************************************/

	//************************************
	// ��������: CChartXYAxis
	// ��������: 
	// ������Ϣ: void
	// ����˵��: 
	//************************************
	CChartXYAxis::CChartXYAxis( void ) :
		m_bVisibelCustomTick(true),			//�Ƿ���ʾ�Զ���̶�
		m_bVisibleBaseLine(true),			//�Ƿ���ʾ����
		m_iMinTick(0),						//�̶���Сֵ
		m_iMaxTick(5),						//�̶����ֵ
		m_iMinTickEx(0),					//���ӿ̶���Сֵ
		m_iMaxTickEx(5),					//���ӿ̶����ֵ
		m_uStepTick(1),						//�̶ȼ��
		m_iMaxGraphWidth(0),				//ͼ����ͼ����������
		m_iMaxGraphHeight(0),				//ͼ����ͼ�������߶�
		m_uMaxAxisLabelWidth(0),			//ͼ���������ǩ������
		m_uMaxAxisLabelHeight(16),			//ͼ���������ǩ���߶�
		m_uMaxDataLabelWidth(25),			//ͼ�����ݿ̶�����
		m_uLegendLocation(LOCATION_BOTTOM),	//ͼ��λ��
		m_uLabelLocation(LOCATION_BOTTOM),	//�����ǩ�̶�λ��
		m_uAlignment(CHART_HORIZONTAL),		//ͼ�����򡣱�ͼ�����Ը�ֵ
		m_uXYAxisFontId(0),					//�̶���������ID
		m_uXYAxisLineSize(2),				//�̶�������С
		m_uLegendMaxWidth(60),				//ͼ�����������
		m_uLegendMaxHeight(22),				//ͼ��������߶�
		m_dDataScale(0.0),					//һ�����ݵ�λ��ռ�õ�����
		m_iAxissCale(0),					//����λ��
		m_iMaxBaseLine(0),					//�������ֵ
		m_iMinBaseLine(0),					//������Сֵ
		m_dXYAxisLineColor(0xFF000000),		//�̶�������ɫ
		m_pChartView(NULL)
	{
		m_sLegendTitel			= _T("Legend");
		m_rcChartPadding.left	= 5;
		m_rcChartPadding.top	= 5;
		m_rcChartPadding.right	= 5;
		m_rcChartPadding.bottom	= 5;
		SetTickLimis(GetMinTick(),GetMaxTick(),GetSetpTick());
	}

	//************************************
	// ��������: ~CChartXYAxis
	// ��������: 
	// ������Ϣ: void
	// ����˵��: 
	//************************************
	CChartXYAxis::~CChartXYAxis( void )
	{

	}

	//************************************
	// ��������: SetTickLimis
	// ��������: void
	// ������Ϣ: int _MinTick
	// ������Ϣ: int _MaxTick
	// ������Ϣ: UINT _StepTick
	// ����˵��: 
	//************************************
	void CChartXYAxis::SetTickLimis( int _MinTick,int _MaxTick,UINT _StepTick )
	{
		m_iMinTick	= _MinTick<GetMinTick()?_MinTick:m_iMinTick;
		m_iMaxTick	= _MaxTick>GetMaxTick()?_MaxTick:m_iMaxTick;
		m_uStepTick	= (_StepTick<=0||_StepTick < GetSetpTick())?(int)((m_iMaxTick - m_iMinTick)/5):_StepTick;
		m_rDataAxis.Empty();

		if(_StepTick){
			m_rDataAxis.Add(0);
			for(int nIndex = _StepTick;nIndex < _MaxTick;nIndex += _StepTick){
				m_rDataAxis.Add(nIndex);
			}
			for(int nIndex = 0-_StepTick;nIndex > _MinTick;nIndex -= _StepTick){
				m_rDataAxis.Add(nIndex);
			}
			m_rDataAxis.Add(_MinTick);
			m_rDataAxis.Add(_MaxTick);
		}

		Invalidate();
	}

	//************************************
	// ��������: SetMinTick
	// ��������: void
	// ������Ϣ: int _MinTick
	// ����˵��: 
	//************************************
	void CChartXYAxis::SetMinTick( int _MinTick )
	{
		SetTickLimis(_MinTick,GetMaxTick(),GetSetpTick());
	}

	//************************************
	// ��������: SetMaxTick
	// ��������: void
	// ������Ϣ: int _MaxTick
	// ����˵��: 
	//************************************
	void CChartXYAxis::SetMaxTick( int _MaxTick )
	{
		SetTickLimis(GetMinTick(),_MaxTick,GetSetpTick());
	}

	//************************************
	// ��������: SetStepTick
	// ��������: void
	// ������Ϣ: int _StepTick
	// ����˵����#end$
	//************************************
	void CChartXYAxis::SetStepTick( int _StepTick /*= 0*/ )
	{
		SetTickLimis(GetMinTick(),GetMaxTick(),_StepTick);
	}

	//************************************
	// ��������: GetMinTick
	// ��������: int
	// ����˵��: 
	//************************************
	int CChartXYAxis::GetMinTick()
	{
		return m_iMinTick < m_iMinTickEx?m_iMinTick:m_iMinTickEx;
	}

	//************************************
	// ��������: GetMaxTick
	// ��������: int
	// ����˵��: 
	//************************************
	int CChartXYAxis::GetMaxTick()
	{
		return m_iMaxTick > m_iMaxTickEx?m_iMaxTick:m_iMaxTickEx;
	}

	//************************************
	// ��������: GetSetpTick
	// ��������: UINT
	// ����˵��: 
	//************************************
	UINT CChartXYAxis::GetSetpTick()
	{
		return m_uStepTick;
	}
	
	//************************************
	// ��������: ResetTick
	// ��������: void
	// ����˵����#end$
	//************************************
	void CChartXYAxis::ResetTick()
	{
		m_iMaxTick		= 0;
		m_iMaxTickEx	= 5;
		m_iMinTick		= 0;
		m_iMinTickEx	= 5;
		m_uStepTick		= 1;

		SetTickLimis(GetMinTick(),GetMaxTick(),GetSetpTick());
	}

	//************************************
	// ��������: AddLabel
	// ��������: void
	// ������Ϣ: LPCTSTR _DataLabel
	// ����˵��: 
	//************************************
	void CChartXYAxis::AddLabel( LPCTSTR _DataLabel )
	{
		m_rChartLabels.Add(_DataLabel);
		Invalidate();
	}

	//************************************
	// ��������: AddCustomTick
	// ��������: void
	// ������Ϣ: int _TickValue
	// ����˵��: 
	//************************************
	void CChartXYAxis::AddCustomTick( int _TickValue )
	{
		m_rDataCustomAxis.Add(_TickValue);
		if(_TickValue > m_iMaxTickEx)
			m_iMaxTickEx = _TickValue;
		if(_TickValue < m_iMinTickEx)
			m_iMinTickEx = _TickValue;

		Invalidate();
	}

	//************************************
	// ��������: SetVisibleCoustomTick
	// ��������: void
	// ������Ϣ: bool _Visible
	// ����˵��: 
	//************************************
	void CChartXYAxis::SetVisibleCoustomTick( bool _Visible )
	{
		m_bVisibelCustomTick = _Visible;
		Invalidate();
	}

	//************************************
	// ��������: GetVisibleCoustomTick
	// ��������: bool
	// ����˵��: 
	//************************************
	bool CChartXYAxis::GetVisibleCoustomTick()
	{
		return m_bVisibelCustomTick;
	}

	//************************************
	// ��������: SetXYAxisFontId
	// ��������: void
	// ������Ϣ: int _FontId
	// ����˵��: 
	//************************************
	void CChartXYAxis::SetXYAxisFontId( int _FontId )
	{
		if(_FontId >= 0){
			m_uXYAxisFontId = _FontId;
			Invalidate();
		}
	}

	//************************************
	// ��������: GetXYAxisFontId
	// ��������: int
	// ����˵��: 
	//************************************
	int CChartXYAxis::GetXYAxisFontId()
	{
		return m_uXYAxisFontId;
	}

	//************************************
	// ��������: SetXYAxisLineSize
	// ��������: void
	// ������Ϣ: UINT _LineSize
	// ����˵��: 
	//************************************
	void CChartXYAxis::SetXYAxisLineSize( UINT _LineSize )
	{
		m_uXYAxisLineSize	= _LineSize;
		Invalidate();
	}

	//************************************
	// ��������: GetXYAxisLineSize
	// ��������: UINT
	// ����˵��: 
	//************************************
	UINT CChartXYAxis::GetXYAxisLineSize()
	{
		return m_uXYAxisLineSize;
	}
	
	//************************************
	// ��������: SetLegendMaxWidth
	// ��������: void
	// ������Ϣ: UINT _LegendMaxWidth
	// ����˵��: 
	//************************************
	void CChartXYAxis::SetLegendMaxWidth( UINT _LegendMaxWidth )
	{
		m_uLegendMaxWidth	= _LegendMaxWidth;
		Invalidate();
	}

	//************************************
	// ��������: GetLegendMaxWidth
	// ��������: UINT
	// ����˵��: 
	//************************************
	UINT CChartXYAxis::GetLegendMaxWidth()
	{
		return m_uLegendMaxWidth;
	}

	//************************************
	// ��������: SetLegendMaxHeight
	// ��������: void
	// ������Ϣ: UINT _LegendMaxHeight
	// ����˵��: 
	//************************************
	void CChartXYAxis::SetLegendMaxHeight( UINT _LegendMaxHeight )
	{
		m_uLegendMaxHeight	= _LegendMaxHeight;
		Invalidate();
	}

	//************************************
	// ��������: GetLegendMaxHeight
	// ��������: UINT
	// ����˵��: 
	//************************************
	UINT CChartXYAxis::GetLegendMaxHeight()
	{
		return m_uLegendMaxHeight;
	}

	//************************************
	// ��������: GetMaxGraphWidth
	// ��������: int 
	// ����˵��: 
	//************************************
	int CChartXYAxis::GetMaxGraphWidth()
	{
		return m_iMaxGraphWidth;
	}

	//************************************
	// ��������: GetMaxGraphHeight
	// ��������: int 
	// ����˵��: 
	//************************************
	int CChartXYAxis::GetMaxGraphHeight()
	{
		return m_iMaxGraphHeight;
	}

	//************************************
	// ��������: SetMaxAxisLabelWidth
	// ��������: void
	// ������Ϣ: UINT _AxisLabelWidth
	// ����˵��: 
	//************************************
	void CChartXYAxis::SetMaxAxisLabelWidth( UINT _AxisLabelWidth )
	{
		m_uMaxAxisLabelWidth	= _AxisLabelWidth;
		Invalidate();
	}

	//************************************
	// ��������: GetMaxAxisLabelWidth
	// ��������: UINT
	// ����˵��: 
	//************************************
	UINT CChartXYAxis::GetMaxAxisLabelWidth()
	{
		return m_uMaxAxisLabelWidth;
	}

	//************************************
	// ��������: SetMaxAxisLabelHeight
	// ��������: void
	// ������Ϣ: UINT _AxisLabelHeight
	// ����˵��: 
	//************************************
	void CChartXYAxis::SetMaxAxisLabelHeight( UINT _AxisLabelHeight )
	{
		m_uMaxAxisLabelHeight = _AxisLabelHeight;
		Invalidate();
	}

	//************************************
	// ��������: GetMaxAxisLabelHeight
	// ��������: UINT
	// ����˵��: 
	//************************************
	UINT CChartXYAxis::GetMaxAxisLabelHeight()
	{
		return m_uMaxAxisLabelHeight;
	}

	//************************************
	// ��������: SetMaxDataLabelWidth
	// ��������: void
	// ������Ϣ: UINT _DataLabelWidth
	// ����˵����#end$
	//************************************
	void CChartXYAxis::SetMaxDataLabelWidth( UINT _DataLabelWidth )
	{
		m_uMaxDataLabelWidth = _DataLabelWidth;
	}

	//************************************
	// ��������: GetMaxDataLabelWidth
	// ��������: UINT
	// ����˵����#end$
	//************************************
	UINT CChartXYAxis::GetMaxDataLabelWidth()
	{
		return m_uMaxDataLabelWidth;
	}

	//************************************
	// ��������: SetLegendLocation
	// ��������: void
	// ������Ϣ: lalign _LegendLocation
	// ����˵��: 
	//************************************
	void CChartXYAxis::SetLegendLocation( lalign _LegendLocation )
	{
		m_uLegendLocation	= _LegendLocation;
		Invalidate();
	}

	//************************************
	// ��������: GetLegendLocation
	// ��������: UiLib::lalign
	// ����˵��: 
	//************************************
	UiLib::lalign CChartXYAxis::GetLegendLocation()
	{
		return m_uLegendLocation;
	}

	//************************************
	// ��������: SetXYAxisLineColor
	// ��������: void
	// ������Ϣ: DWORD _LineColor
	// ����˵��: 
	//************************************
	void CChartXYAxis::SetXYAxisLineColor( DWORD _LineColor )
	{
		m_dXYAxisLineColor = _LineColor;
		Invalidate();
	}

	//************************************
	// ��������: SetXYAxisLineColor
	// ��������: void
	// ������Ϣ: LPCTSTR _LineColor
	// ����˵��: 
	//************************************
	void CChartXYAxis::SetXYAxisLineColor( LPCTSTR _LineColor )
	{
		if(_LineColor){
			if( *_LineColor == _T('#'))
				_LineColor = ::CharNext(_LineColor);
			LPTSTR pstr = NULL;
			SetXYAxisLineColor(_tcstoul(_LineColor, &pstr, 16));
			Invalidate();
		}
	}

	//************************************
	// ��������: GetXYAxisLineColor
	// ��������: DWORD
	// ����˵��: 
	//************************************
	DWORD CChartXYAxis::GetXYAxisLineColor()
	{
		return m_dXYAxisLineColor;
	}

	//************************************
	// ��������: SetChartViewObj
	// ��������: void
	// ������Ϣ: CChartViewUI * _pChartViewUI
	// ����˵��: 
	//************************************
	void CChartXYAxis::SetChartViewObj( CChartViewUI* _pChartViewUI )
	{
		m_pChartView = _pChartViewUI;
	}

	//************************************
	// ��������: Invalidate
	// ��������: void
	// ����˵��: 
	//************************************
	void CChartXYAxis::Invalidate()
	{
		if(m_pChartView)
			m_pChartView->Invalidate();
	}

	//************************************
	// ��������: DrawAxis
	// ��������: void
	// ������Ϣ: HDC hDC
	// ������Ϣ: RECT & rcPaint
	// ������Ϣ: RECT & rcItem
	// ����˵��: 
	//************************************
	void CChartXYAxis::DrawAxis( HDC hDC, const RECT& rcPaint,RECT& rcItem )
	{
		rcItem.left		+= m_rcChartPadding.left;
		rcItem.top		+= m_rcChartPadding.top;
		rcItem.right	-= m_rcChartPadding.right;
		rcItem.bottom	-= m_rcChartPadding.bottom;

		RECT nRc		= rcItem;

		//����ͼ�����ռλ
		if(m_uLegendLocation == LOCATION_TOP)
			nRc.top		= nRc.top + m_uLegendMaxHeight + 6;
		else if(m_uLegendLocation == LOCATION_BOTTOM)
			nRc.bottom	= nRc.bottom - m_uLegendMaxHeight - 6;
		else if(m_uLegendLocation == LOCATION_RIGHT)
			nRc.right	= nRc.right - m_uLegendMaxWidth;

		//����̶ȱ�ǩռλ
		if(m_uAlignment == CHART_HORIZONTAL){
			//�����ǩռλ
			if(m_uLabelLocation == LOCATION_TOP)
				nRc.top += m_uMaxAxisLabelHeight;
			else if(m_uLabelLocation == LOCATION_BOTTOM)
				nRc.bottom -= m_uMaxAxisLabelHeight;

			//�������ݿ̶�ռλ
			nRc.left += m_uMaxDataLabelWidth;
		}
		else if(m_uAlignment == CHART_VERTICAL){

		}

		nRc.top += 5;

		m_iMaxGraphWidth	= nRc.right - nRc.left;
		m_iMaxGraphHeight	= nRc.bottom - nRc.top;

		if(m_uAlignment == CHART_HORIZONTAL && m_iMaxGraphWidth > 0 && m_iMaxGraphHeight > 0){
			m_dDataScale	= GetTickCount() == 0?nRc.bottom:1.00 * m_iMaxGraphHeight / ((GetMinTick() - GetMinTick()*2) + GetMaxTick());
			m_iAxissCale	= GetTickCount() == 0?nRc.bottom:nRc.top + (int)(GetMaxTick() * m_dDataScale);
			m_iMinBaseLine	= 0;

			//��Y��
			RECT nRcYAxis = {0};
			nRcYAxis.left	= nRc.left;
			nRcYAxis.top	= nRc.top - 5;
			nRcYAxis.right	= nRc.left;
			nRcYAxis.bottom	= nRc.bottom + 3;
			CRenderEngine::DrawLine(hDC,nRcYAxis,m_uXYAxisLineSize,m_dXYAxisLineColor);

			//��Y��̶�
			for(int nIndex = 0;nIndex < m_rDataAxis.GetSize();nIndex++){
				RECT nRcItemYAxis		= {0};
				RECT nRcItemYAxisEx		= {0};
				RECT nRcItemYText		= {0};

				int nValue = m_rDataAxis.GetAt(nIndex);


				int nValueScale			= (int)((nValue > 0?nValue:(nValue - nValue*2))* m_dDataScale);
				nRcItemYAxis.right		= nRcYAxis.left - 5;
				nRcItemYAxis.left		= nRcYAxis.left;
				nRcItemYAxis.top		= nValue > 0?m_iAxissCale - nValueScale:m_iAxissCale + nValueScale;
				nRcItemYAxis.bottom		= nRcItemYAxis.top;

				nRcItemYAxisEx.left		= nRcYAxis.left;
				nRcItemYAxisEx.right	= nRc.right;
				nRcItemYAxisEx.top		= nRcItemYAxis.top;
				nRcItemYAxisEx.bottom	= nRcItemYAxis.bottom;

				if(nValue == GetMaxTick())
					m_iMaxBaseLine		= nRcItemYAxisEx.top;
				if(nValue == GetMinTick())
					m_iMinBaseLine		= nRcItemYAxisEx.top;

				//���ƻ���
				if(GetVisibleBaseLine())
					CRenderEngine::DrawLine(hDC,nRcItemYAxisEx,m_uXYAxisLineSize,RGB(CutColor(m_dXYAxisLineColor,20),CutColor(m_dXYAxisLineColor,20),CutColor(m_dXYAxisLineColor,20)));

				CRenderEngine::DrawLine(hDC,nRcItemYAxis,m_uXYAxisLineSize,m_dXYAxisLineColor);
				
				CDuiString sValue;
				sValue.Format(_T("%d%s"),nValue > 10000?nValue/1000:nValue,nValue > 10000?_T("K"):_T(""));

				nRcItemYText.left	= nRcYAxis.left - m_uMaxDataLabelWidth;
				nRcItemYText.right	= nRcYAxis.left - 5;
				nRcItemYText.top	= nRcItemYAxis.top - 5;
				nRcItemYText.bottom	= nRcItemYAxis.top + 5;

				CRenderEngine::DrawText(hDC,m_pChartView->GetManager(),nRcItemYText,sValue.GetData(),m_dXYAxisLineColor,m_uXYAxisFontId,DT_RIGHT|DT_VCENTER|DT_SINGLELINE);
			}

			//��X��
			RECT nRcXAxis = {0};
			nRcXAxis.left	= nRcYAxis.left;
			nRcXAxis.top	= m_iAxissCale;
			nRcXAxis.right	= nRc.right;
			nRcXAxis.bottom	= nRcXAxis.top;
			CRenderEngine::DrawLine(hDC,nRcXAxis,m_uXYAxisLineSize,m_dXYAxisLineColor);

			double nGroupScale		= (double)(m_iMaxGraphWidth / m_rChartLabels.GetSize());
			double nItemScale		= (double)(nGroupScale / (m_pChartView->GetSeriesCount()+1));
			double nGroupSpace		= (double)(nItemScale / 2);
			double nItemSpace		= (double)(nGroupSpace / 10);

			//��X��̶�
			for(int nSeriesIndex = 0;(UINT)nSeriesIndex < m_pChartView->GetSeriesCount();nSeriesIndex++){
				CChartSeries* pSeries = m_pChartView->GetSeries(nSeriesIndex);
				if(!pSeries)
					continue;
			
				for(int nIndex = 0;nIndex < m_rChartLabels.GetSize() && nIndex < pSeries->GetDataCount();nIndex++){
					CChartItem* pItem		= pSeries->GetSeriesData(nIndex);
					if(!pItem)
						continue;

					RECT nRcItemXBar		= {0};
					
					nRcItemXBar.left		= (int)(nRcYAxis.left + nGroupScale*nIndex + nGroupSpace + nItemScale*nSeriesIndex);
					nRcItemXBar.right		= (int)(nRcItemXBar.left + nItemScale - nItemSpace);
					nRcItemXBar.top			= pItem->GetDataValue()>0?(int)(m_iAxissCale - pItem->GetDataValue()*m_dDataScale):(int)(m_iAxissCale + (pItem->GetDataValue() - pItem->GetDataValue()*2)*m_dDataScale);
					nRcItemXBar.bottom		= m_iAxissCale;

					CRenderEngine::DrawGradient(hDC,nRcItemXBar,pSeries->GetSeriesColorA(),pSeries->GetSeriesColorB(),false,16);
					CRenderEngine::DrawRect(hDC,nRcItemXBar,1,m_dXYAxisLineColor);

					RECT nRcItemXAxis		= {0};

					nRcItemXAxis.left		= (int)(nRcYAxis.left + nGroupScale*(nIndex+1) - nItemSpace/2);
					nRcItemXAxis.right		= nRcItemXAxis.left;
					nRcItemXAxis.top		= m_iMinBaseLine + 2;
					nRcItemXAxis.bottom		= m_iMinBaseLine - 3;

					CRenderEngine::DrawLine(hDC,nRcItemXAxis,m_uXYAxisLineSize,RGB(CutColor(m_dXYAxisLineColor,75),CutColor(m_dXYAxisLineColor,75),CutColor(m_dXYAxisLineColor,75)));

					nRcItemXAxis.top		= m_iAxissCale + 2;
					nRcItemXAxis.bottom		= m_iAxissCale - 3;

					CRenderEngine::DrawLine(hDC,nRcItemXAxis,m_uXYAxisLineSize,m_dXYAxisLineColor);

					if(m_iAxissCale != m_iMinBaseLine){
						nRcItemXAxis.left		= nRcXAxis.right;
						nRcItemXAxis.right		= nRcXAxis.left +1;
						nRcItemXAxis.top		= m_iMinBaseLine;
						nRcItemXAxis.bottom		= m_iMinBaseLine;

						CRenderEngine::DrawLine(hDC,nRcItemXAxis,m_uXYAxisLineSize,RGB(CutColor(m_dXYAxisLineColor,75),CutColor(m_dXYAxisLineColor,75),CutColor(m_dXYAxisLineColor,75)));
					}

					CDuiString nRcGroupXText	= m_rChartLabels.GetAt(nIndex);
					RECT nRcItemXText		= {0};
					nRcItemXText.left		= (int)(nRcYAxis.left + nGroupScale*nIndex);
					nRcItemXText.right		= (int)(nRcYAxis.left + nGroupScale*(nIndex+1) - nItemSpace/2);
					nRcItemXText.top		= m_iMinBaseLine;
					nRcItemXText.bottom		= m_iMinBaseLine + m_uMaxAxisLabelHeight;
					
					CRenderEngine::DrawText(hDC,m_pChartView->GetManager(),nRcItemXText,nRcGroupXText.GetData(),m_dXYAxisLineColor,m_uXYAxisFontId,DT_CENTER|DT_VCENTER|DT_SINGLELINE);
				}
			}
			//������ͼ��
			if(m_pChartView->GetSeriesCount()){
				if(m_uLegendLocation == LOCATION_RIGHT){
					int	nSeriesLegendHeight	= m_uLegendMaxHeight*(m_pChartView->GetSeriesCount()+1)+8;
					int nSeriesLegendWidth	= m_uLegendMaxWidth - 32;

					if(m_iMaxGraphHeight > nSeriesLegendHeight){
						RECT nRcSeriesLegend	= {0};
						nRcSeriesLegend.left	= nRcXAxis.right + 8;
						nRcSeriesLegend.right	= nRcSeriesLegend.left + m_uLegendMaxWidth -8;
						nRcSeriesLegend.top		= nRc.top + (int)(m_iMaxGraphHeight - nSeriesLegendHeight)/2;
						nRcSeriesLegend.bottom	= nRc.bottom - (int)(m_iMaxGraphHeight - nSeriesLegendHeight)/2;

						CRenderEngine::DrawRect(hDC,nRcSeriesLegend,1,m_dXYAxisLineColor);

						for(int nSeriesIndex = 0;(UINT)nSeriesIndex < m_pChartView->GetSeriesCount();nSeriesIndex++){

							if(nSeriesIndex == 0){
								RECT nRcLegendTitleText		= {0};
								nRcLegendTitleText.left		= nRcSeriesLegend.left;
								nRcLegendTitleText.right	= nRcSeriesLegend.right;
								nRcLegendTitleText.top		= nRcSeriesLegend.top;
								nRcLegendTitleText.bottom	= nRcLegendTitleText.top+m_uLegendMaxHeight;

								CRenderEngine::DrawText(hDC,m_pChartView->GetManager(),nRcLegendTitleText,m_sLegendTitel.GetData(),m_dXYAxisLineColor,m_uXYAxisFontId,DT_CENTER|DT_VCENTER|DT_SINGLELINE);
							}
							CChartSeries* pSeries	= m_pChartView->GetSeries(nSeriesIndex);

							if(!pSeries)
								continue;

							RECT nRcLegendText		= {0};
							nRcLegendText.left		= nRcSeriesLegend.left + 5;
							nRcLegendText.right		= nRcLegendText.left + m_uLegendMaxWidth - 40;
							nRcLegendText.top		= nRcSeriesLegend.top+m_uLegendMaxHeight + 2 + m_uLegendMaxHeight*nSeriesIndex;
							nRcLegendText.bottom	= nRcLegendText.top + m_uLegendMaxHeight + 2;

							CRenderEngine::DrawText(hDC,m_pChartView->GetManager(),nRcLegendText,pSeries->GetLegendText(),m_dXYAxisLineColor,m_uXYAxisFontId,DT_LEFT|DT_VCENTER|DT_SINGLELINE);
							
							RECT nRcLegendBar		= {0};
							nRcLegendBar.left		= nRcLegendText.right + 5;
							nRcLegendBar.right		= nRcSeriesLegend.right - 5;
							nRcLegendBar.top		= nRcLegendText.top + 5;
							nRcLegendBar.bottom		= nRcLegendText.bottom - 5;

							CRenderEngine::DrawGradient(hDC,nRcLegendBar,pSeries->GetSeriesColorA(),pSeries->GetSeriesColorB(),false,16);
							CRenderEngine::DrawRect(hDC,nRcLegendBar,1,m_dXYAxisLineColor);
						}
					}
				}
				else if(m_uLegendLocation == LOCATION_TOP || m_uLegendLocation == LOCATION_BOTTOM){

					int nSeriesLegendHeight		= m_uLegendMaxHeight;
					int nSeriesLegendWidth		= m_uLegendMaxWidth*m_pChartView->GetSeriesCount();

					RECT nRcSeriesLegend		= {0};
					nRcSeriesLegend.left	= nRcYAxis.left + (int)(m_iMaxGraphWidth - nSeriesLegendWidth)/2 + 2;
					if(m_uLegendLocation == LOCATION_TOP){
						nRcSeriesLegend.top		= nRc.top - 6 - nSeriesLegendHeight - 5;
						nRcSeriesLegend.bottom	= nRc.top - 6 - 5;
					}
					else if(m_uLegendLocation == LOCATION_BOTTOM){
						nRcSeriesLegend.top		= m_uLabelLocation == LOCATION_BOTTOM?nRc.bottom + nSeriesLegendHeight:nRc.bottom + 6 + nSeriesLegendHeight;
						nRcSeriesLegend.bottom	= nRcSeriesLegend.top + m_uLegendMaxHeight;
					}
					nRcSeriesLegend.right		= nRcXAxis.right - (int)(m_iMaxGraphWidth - nSeriesLegendWidth)/2 - 2;

					CRenderEngine::DrawRect(hDC,nRcSeriesLegend,1,m_dXYAxisLineColor);

					for(int nSeriesIndex = 0;(UINT)nSeriesIndex < m_pChartView->GetSeriesCount();nSeriesIndex++){
						CChartSeries* pSeries	= m_pChartView->GetSeries(nSeriesIndex);

						if(!pSeries)
							continue;

						RECT nRcLegendText		= {0};
						nRcLegendText.left		= nRcSeriesLegend.left + m_uLegendMaxWidth * nSeriesIndex + 5;
						nRcLegendText.right		= nRcLegendText.left + m_uLegendMaxWidth - 48;
						nRcLegendText.top		= nRcSeriesLegend.top + 2;
						nRcLegendText.bottom	= nRcSeriesLegend.bottom;

						CRenderEngine::DrawText(hDC,m_pChartView->GetManager(),nRcLegendText,pSeries->GetLegendText(),m_dXYAxisLineColor,m_uXYAxisFontId,DT_LEFT|DT_VCENTER|DT_SINGLELINE);

						RECT nRcLegendBar		= {0};
						nRcLegendBar.left		= nRcLegendText.right + 5;
						nRcLegendBar.right		= nRcLegendText.left + m_uLegendMaxWidth - 15;
						nRcLegendBar.top		= nRcSeriesLegend.top + 4;
						nRcLegendBar.bottom		= nRcSeriesLegend.bottom - 4;

						CRenderEngine::DrawGradient(hDC,nRcLegendBar,pSeries->GetSeriesColorA(),pSeries->GetSeriesColorB(),false,16);
						CRenderEngine::DrawRect(hDC,nRcLegendBar,1,m_dXYAxisLineColor);
					}
				}
			}
		}
		else if(m_uAlignment == CHART_VERTICAL){

		}

		rcItem = nRc;
	}

	//************************************
	// ��������: CalLegendSize
	// ��������: void
	// ������Ϣ: CChartSeries * _ChartSeries
	// ����˵��: 
	//************************************
	void CChartXYAxis::CalLegendSize(HDC hDC)
	{
		for(int iIndex = 0;iIndex < m_rChartLabels.GetSize();iIndex++){
			CDuiString nText = m_rChartLabels.GetAt(iIndex).GetData();
		}
	}

	//************************************
	// ��������: CalMaxAxisLabelWidth
	// ��������: void
	// ������Ϣ: HDC hDC
	// ������Ϣ: CChartSeries * _ChartSeries
	// ����˵��: 
	//************************************
	void CChartXYAxis::CalMaxAxisLabelWidth( HDC hDC,CChartSeries* _ChartSeries )
	{
		for(int iIndex = 0;iIndex < m_rChartLabels.GetSize();iIndex++){
			CDuiString nText = m_rChartLabels.GetAt(iIndex).GetData();

			if(nText.GetLength()){
				SIZE nSize	= {0};
				GetTextExtentPoint32(hDC,nText.GetData(),nText.GetLength(),&nSize);

				if((UINT)nSize.cx > GetMaxAxisLabelWidth())
					SetMaxAxisLabelWidth(nSize.cx);
			}
		}
	}

	//************************************
	// ��������: CalMaxDataLabelWidth
	// ��������: void
	// ������Ϣ: HDC hDC
	// ������Ϣ: CChartSeries * _ChartSeries
	// ����˵����#end$
	//************************************
	void CChartXYAxis::CalMaxDataLabelWidth( HDC hDC,CChartSeries* _ChartSeries )
	{
		for(int iIndex = 0;iIndex < m_rChartLabels.GetSize();iIndex++){
			CChartItem* pItem = _ChartSeries->GetSeriesData(iIndex);
			if(!pItem)
				continue;

			CDuiString nDataText;
			nDataText.Format(_T("%d%s"),pItem->GetDataValue() > 10000?(int)(pItem->GetDataValue()/1000):(int)(pItem->GetDataValue()),pItem->GetDataValue() > 10000?_T("K"):_T(""));

			if(nDataText.GetLength()){
				SIZE nSize = {0};
				GetTextExtentPoint32(hDC,nDataText.GetData(),nDataText.GetLength(),&nSize);
				if((UINT)nSize.cx > GetMaxDataLabelWidth())
					SetMaxDataLabelWidth(nSize.cx);
			}
		}
	}

	//************************************
	// ��������: CalAxisDataLimits
	// ��������: void
	// ������Ϣ: CChartSeries * _ChartSeries
	// ����˵����#end$
	//************************************
	void CChartXYAxis::CalAxisDataLimits( CChartSeries* _ChartSeries )
	{
		for(int iIndex = 0;iIndex < m_rChartLabels.GetSize();iIndex++){
			CChartItem* pItem = _ChartSeries->GetSeriesData(iIndex);
			if(!pItem)
				continue;

			if(pItem->GetDataValue() > GetMaxTick())
				SetMaxTick((int)(pItem->GetDataValue()));
			if(pItem->GetDataValue() < GetMinTick())
				SetMinTick((int)(pItem->GetDataValue()));

			int aa = (GetMaxTick() - GetMinTick())/5;
			int bb =  GetSetpTick();

			if((UINT)((GetMaxTick() - GetMinTick())/5) > GetSetpTick())
				SetStepTick((int)((GetMaxTick() - GetMinTick())/5));

			if(pItem->GetDataValue() > GetMaxTick())
				SetMaxTick((int)(pItem->GetDataValue()));
			if(pItem->GetDataValue() < GetMinTick())
				SetMinTick((int)(pItem->GetDataValue()));
		}
	}

	//************************************
	// ��������: RemoveAllDataLabel
	// ��������: void
	// ����˵��: 
	//************************************
	void CChartXYAxis::RemoveAllDataLabel()
	{
		m_rChartLabels.Empty();
	}

	//************************************
	// ��������: GetGroupCount
	// ��������: UINT
	// ����˵��: 
	//************************************
	UINT CChartXYAxis::GetGroupCount()
	{
		return m_rChartLabels.GetSize();
	}

	//************************************
	// ��������: GetTickCount
	// ��������: UINT
	// ����˵����#end$
	//************************************
	UINT CChartXYAxis::GetTickCount()
	{
		return m_rDataAxis.GetSize() + (m_bVisibelCustomTick ? m_rDataCustomAxis.GetSize():0);
	}

	//************************************
	// ��������: AddColor
	// ��������: DWORD
	// ������Ϣ: DWORD _SrcValue
	// ������Ϣ: DWORD _AddValue
	// ����˵��: 
	//************************************
	DWORD CChartXYAxis::AddColor( DWORD _SrcValue,DWORD _AddValue )
	{
		if((_SrcValue + _AddValue) > 255)
			return 255;

		return _SrcValue + _AddValue;
	}

	//************************************
	// ��������: CutColor
	// ��������: DWORD
	// ������Ϣ: DWORD _SrcValue
	// ������Ϣ: DWORD _CurValue
	// ����˵��: 
	//************************************
	DWORD CChartXYAxis::CutColor( DWORD _SrcValue,DWORD _CurValue )
	{
		if((_SrcValue - _CurValue) < 0)
			return 0;

		return _SrcValue - _CurValue;
	}

	//************************************
	// ��������: SetVisibleBaseLine
	// ��������: void
	// ������Ϣ: bool _Visible
	// ����˵��: 
	//************************************
	void CChartXYAxis::SetVisibleBaseLine( bool _Visible )
	{
		m_bVisibleBaseLine = _Visible;
	}

	//************************************
	// ��������: GetVisibleBaseLine
	// ��������: bool
	// ����˵��: 
	//************************************
	bool CChartXYAxis::GetVisibleBaseLine()
	{
		return m_bVisibleBaseLine;
	}

	/**************************************************************************************************************************************************************************************************/
	/*
	/**************************************************************************************************************************************************************************************************/

	//************************************
	// ��������: CChartViewUI
	// ��������: 
	// ������Ϣ: void
	// ����˵��: 
	//************************************
	CChartViewUI::CChartViewUI( void )
	{
		m_cXYAxis.SetChartViewObj(this);
	}

	//************************************
	// ��������: ~CChartViewUI
	// ��������: 
	// ����˵��: 
	//************************************
	CChartViewUI::~CChartViewUI(void)
	{

	}

	//************************************
	// ��������: GetClass
	// ��������: LPCTSTR
	// ����˵��: 
	//************************************
	LPCTSTR CChartViewUI::GetClass() const
	{
		return _T("ChartView");
	}

	//************************************
	// ��������: GetInterface
	// ��������: LPVOID
	// ������Ϣ: LPCTSTR pstrName
	// ����˵��: 
	//************************************
	LPVOID CChartViewUI::GetInterface( LPCTSTR pstrName )
	{
		if( _tcscmp(pstrName, _T("ChartView")) == 0 ) return static_cast<CChartViewUI*>(this);
		else return CHorizontalLayoutUI::GetInterface(pstrName);
	}
	
	//************************************
	// ��������: DoPaint
	// ��������: void
	// ������Ϣ: HDC hDC
	// ������Ϣ: const RECT & rcPaint
	// ����˵��: 
	//************************************
	void CChartViewUI::DoPaint( HDC hDC, const RECT& rcPaint )
	{
		if( !::IntersectRect(&m_rcPaint, &rcPaint, &m_rcItem) ) return;
		CHorizontalLayoutUI::DoPaint(hDC,rcPaint);

		if(GetGroupCount()){
			RECT nItem = m_rcItem;
			m_cXYAxis.DrawAxis(hDC,rcPaint,nItem);
		}
	}

	//************************************
	// ��������: AddLabel
	// ��������: void
	// ������Ϣ: LPCTSTR _DataLabel
	// ����˵��: 
	//************************************
	void CChartViewUI::AddLabel( LPCTSTR _DataLabel )
	{
		m_cXYAxis.AddLabel(_DataLabel);
	}

	//************************************
	// ��������: AddSeries
	// ��������: void
	// ������Ϣ: CChartSeries * _ChartSeries
	// ����˵��: 
	//************************************
	void CChartViewUI::AddSeries( CChartSeries* _ChartSeries )
	{
		if(m_rChartSeries.GetSize() == 0)
			m_cXYAxis.ResetTick();

		if(_ChartSeries && m_rChartSeries.Add(_ChartSeries)){
			_ChartSeries->SetChartViewObj(this);
			CalLegendSize(_ChartSeries);
		}
		Invalidate();
	}

	//************************************
	// ��������: GetSeries
	// ��������: CChartSeries*
	// ������Ϣ: LPCTSTR _LegendText
	// ����˵��: 
	//************************************
	CChartSeries* CChartViewUI::GetSeries( LPCTSTR _LegendText )
	{
		for(int iIndex = 0;iIndex < m_rChartSeries.GetSize();iIndex++){
			CChartSeries* pSeries = m_rChartSeries.GetAt(iIndex);
			if(pSeries && _tcscmp(pSeries->GetLegendText(),_LegendText) == 0)
				return pSeries;
		}
		return NULL;
	}

	//************************************
	// ��������: GetSeries
	// ��������: CChartSeries*
	// ������Ϣ: int nIndex
	// ����˵��: 
	//************************************
	CChartSeries* CChartViewUI::GetSeries( int nIndex )
	{
		return m_rChartSeries.GetAt(nIndex);
	}
	
	//************************************
	// ��������: GetSeriesName
	// ��������: UiLib::CDuiString
	// ������Ϣ: int nIndex
	// ����˵��: 
	//************************************
	UiLib::CDuiString CChartViewUI::GetSeriesName( int nIndex )
	{
		CChartSeries* pSeries = m_rChartSeries.GetAt(nIndex);
		if(pSeries)
			return pSeries->GetLegendText();

		return _T("");
	}

	//************************************
	// ��������: SetVisibleSeries
	// ��������: void
	// ������Ϣ: LPCTSTR _LegendText
	// ������Ϣ: bool _Visible
	// ����˵��: 
	//************************************
	void CChartViewUI::SetVisibleSeries( LPCTSTR _LegendText,bool _Visible )
	{
		CChartSeries* pSeries = GetSeries(_LegendText);
		if(pSeries)
			pSeries->SetVisible(_Visible);
	}

	//************************************
	// ��������: GetVisibleSeries
	// ��������: bool
	// ������Ϣ: LPCTSTR _LegendText
	// ����˵��: 
	//************************************
	bool CChartViewUI::GetVisibleSeries( LPCTSTR _LegendText )
	{
		CChartSeries* pSeries = GetSeries(_LegendText);
		if(pSeries)
			return pSeries->GetVisible();

		return false;
	}

	//************************************
	// ��������: CalLegendSize
	// ��������: void
	// ������Ϣ: LPCTSTR _LegendText
	// ������Ϣ: CChartSeries * _ChartSeries
	// ����˵��: 
	//************************************
	void CChartViewUI::CalLegendSize(CChartSeries* _ChartSeries )
	{
		if(_ChartSeries && GetManager() && GetManager()->GetPaintDC()){
			SIZE nSize	= {0};

			CDuiString nSeriesLegendText = _ChartSeries->GetLegendText();

			GetTextExtentPoint32(GetManager()->GetPaintDC(),nSeriesLegendText.GetData(),nSeriesLegendText.GetLength(),&nSize);
			if((UINT)nSize.cx + 36 > m_cXYAxis.GetLegendMaxWidth())
				m_cXYAxis.SetLegendMaxWidth(nSize.cx+36);

			if((UINT)nSize.cy+6 > m_cXYAxis.GetLegendMaxHeight())
				m_cXYAxis.SetLegendMaxHeight(nSize.cy+6);

			m_cXYAxis.CalMaxAxisLabelWidth( GetManager()->GetPaintDC(),_ChartSeries);
			m_cXYAxis.CalMaxDataLabelWidth( GetManager()->GetPaintDC(),_ChartSeries);
			m_cXYAxis.CalAxisDataLimits(_ChartSeries);
		}
	}

	//************************************
	// ��������: GetXYAxis
	// ��������: CChartXYAxis&
	// ����˵��: 
	//************************************
	CChartXYAxis& CChartViewUI::GetXYAxis()
	{
		return m_cXYAxis;
	}
	
	//************************************
	// ��������: RemoveSeries
	// ��������: void
	// ������Ϣ: int _Index
	// ����˵��: 
	//************************************
	void CChartViewUI::RemoveSeries( int _Index )
	{
		CChartSeries* pSeries = m_rChartSeries.GetAt(_Index);
		if(pSeries)
			pSeries->RemoveSeriesDataAll();

		m_rChartSeries.Remove(_Index);

		m_cXYAxis.ResetTick();
		m_cXYAxis.SetMaxDataLabelWidth(25);

		for(int nIndex = 0;nIndex < m_rChartSeries.GetSize();nIndex++){
			CChartSeries* pSeries = m_rChartSeries.GetAt(nIndex);
			if(pSeries){
				m_cXYAxis.CalMaxDataLabelWidth( GetManager()->GetPaintDC(),pSeries);
				m_cXYAxis.CalAxisDataLimits(pSeries);
			}
		}
	}

	//************************************
	// ��������: RemoveSeries
	// ��������: void
	// ������Ϣ: CChartSeries * _ChartSeries
	// ����˵��: 
	//************************************
	void CChartViewUI::RemoveSeries( CChartSeries* _ChartSeries )
	{
		if(!_ChartSeries)
			return;

		_ChartSeries->RemoveSeriesDataAll();

		for(int nIndex = 0;nIndex < m_rChartSeries.GetSize();nIndex++){
			CChartSeries* pSeries = m_rChartSeries.GetAt(nIndex);
			if(pSeries == _ChartSeries)
				RemoveSeries(nIndex);
		}
	}
	//************************************
	// ��������: RemoveAllData
	// ��������: void
	// ����˵��: 
	//************************************
	void CChartViewUI::RemoveAllData()
	{
		for(int nIndex = 0;nIndex < m_rChartSeries.GetSize();nIndex++){
			RemoveSeries(nIndex);
		}
	}

	//************************************
	// ��������: GetGroupCount
	// ��������: UINT
	// ����˵��: 
	//************************************
	UINT CChartViewUI::GetGroupCount()
	{
		return m_cXYAxis.GetGroupCount();
	}

	//************************************
	// ��������: GetSeriesCount
	// ��������: UINT
	// ����˵��: 
	//************************************
	UINT CChartViewUI::GetSeriesCount()
	{
		return m_rChartSeries.GetSize();
	}

}

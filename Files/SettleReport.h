// SettleReport.h: interface for the CSettleReport class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SETTLEREPORT_H__93A44052_3F92_4EF3_9F53_992AE2859126__INCLUDED_)
#define AFX_SETTLEREPORT_H__93A44052_3F92_4EF3_9F53_992AE2859126__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Table.h"

#define TABLE_NAME_SETTLE_REPORT	"settle.rap"
#define MAX_REPORT					2

class CSettleReport : public CTable  
{
public:
	CSettleReport();
	CSettleReport(CSettleEngine::HSettleData settleData);
	virtual ~CSettleReport();

	typedef enum {
		sizeDate  = 7,
		sizeCount =  6, 
		sizeTotal = 12,
	} SettleReportSizes;

	typedef struct _tagSettleReportData {
		uchar m_settleDate			[sizeDate];

		char m_saleCount			[sizeCount + 1];
		char m_saleTotal			[sizeTotal + 1];
		char m_saleVoidCount		[sizeCount + 1];
		char m_saleVoidTotal		[sizeTotal + 1];

		char m_cashLoadCount		[sizeCount + 1];
		char m_cashLoadTotal		[sizeTotal + 1];
		char m_cashLoadVoidCount	[sizeCount + 1];
		char m_cashLoadVoidTotal	[sizeTotal + 1];

		char m_debitLoadCount		[sizeCount + 1];
		char m_debitLoadTotal		[sizeTotal + 1];
		char m_debitLoadVoidCount	[sizeCount + 1];
		char m_debitLoadVoidTotal	[sizeTotal + 1];

		char m_creditLoadCount		[sizeCount + 1];
		char m_creditLoadTotal		[sizeTotal + 1];
		char m_creditLoadVoidCount	[sizeCount + 1];
		char m_creditLoadVoidTotal	[sizeTotal + 1];

		char m_PocharUseCount		[sizeCount + 1];
		char m_PocharUseTotal		[sizeTotal + 1];
		char m_PocharUseVoidCount	[sizeCount + 1];
		char m_PocharUseVoidTotal	[sizeTotal + 1];

		char m_refundCount			[sizeCount + 1];
		char m_refundTotal			[sizeTotal + 1];
		char m_refundVoidCount		[sizeCount + 1];
		char m_refundVoidTotal		[sizeTotal + 1];
	} SettleReportData, *HSettleReportData;

	inline HSettleReportData GetData() { return &this->m_data;};
	void SetData(CSettleEngine::HSettleData settleData);

	virtual int		Append();
	virtual void	PrintAll();

private:
	SettleReportData m_data;
};

#endif // !defined(AFX_SETTLEREPORT_H__93A44052_3F92_4EF3_9F53_992AE2859126__INCLUDED_)

class MemoryPool {

private:

	void *m_Block;

	struct Unit {
		struct Unit *pre, *next;
	}

	
	struct Unit m_UsedBlock;
	struct Unit m_FreeBlock;

	unsigned int m_BlockSize;
	unsigned int m_UnitSize;


public:
	MemoryPool (unsigned unitSize, unsigned num_unit);
	~MemoryPool ();

	void *Allocate(unsigned size);
	void Free(void *p);

};

MemoryPool::MemoryPool(unsigned unitSize, unsigned num_unit) {
	m_UnitSize = unitSize;
	m_BlockSize = (unitSize + sizeof(struct Unit)) * num_unit;
	
	// Allocate Memory Pool
	m_Block = malloc(m_BlockSize);

	// Divide pool into unit
	for (int i = 0; i < num_unit; i++) {
		struct Unit *cur_unit = (struct Unit *) ((char *)m_Block + i * (unitSize + sizeof(struct Unit)));
		cur_unit->pre = NULL;
		cur_unit->next = m_FreeBlock;

		if (m_FreeBlock != NULL)
			m_FreeBlock->pre = cur_unit;

		m_FreeBlock = cur_unit;
	}
}

void* MemoryPool::Allocate(unsigned unitSize) {
	if (unitSize > m_UnitSize || m_FreeBlock == NULL)
		return malloc(unitSize);

	struct Unit * cur_unit = m_FreeBlock;

	// Break current unit from free pool
	m_FreeBlock = m_FreeBlock->next;
	
	if (m_FreeBlock != NULL) {
		m_FreeBlock->pre = NULL;
	}

	cur_unit->next = m_UsedBlock;

	if (m_UsedBlock != NULL) {
		m_UsedBlock->pre = cur_unit;
	}
	m_UsedBlock = cur_unit;

	return (void *) ((char *) cur_unit + sizeof(struct Unit));

}

void MemoryPool::Free(void *p) {
	struct Unit * cur_unit = (void *) ((char *)p - sizeof(struct Unit));

	m_UsedBlock = m_UsedBlock->next;
}

MemoryPool::~MemoryPool() {
	free(m_MemoryBlock);
}